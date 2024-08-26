#include <libprcpp/interfaces/iscylladb_core_interface.h>

#include <libprcpp/modules/system_module.h>
#include <libprcpp/modules/utility_module.h>

#include <thread>
#include <memory>
#include <future>

using namespace libprcpp;

///////////////////////////////////////////////////////////////////////

std::mutex printMutex;

class CBaseDb final : public IScyllaDbCoreInterface
{
private:
    TScyllaDbConnection m_conn;

    const std::string TABLE_NAME = "tb_uuidv4_collide";

public:
    CBaseDb(/* args */)
    {
        const auto CONFIG = utilityFunctions::json::fromFile("../../../test/test_scylladb_uuidv4_nochecking/config.json");

        TScyllaDbConnection conn;

        conn.auth_mode = (EScyllaDbAuthMode::Enum)CONFIG["connection"]["auth"].asInt();
        conn.host = CONFIG["connection"]["hosts"].asString();
        conn.username = CONFIG["connection"]["username"].asString();
        conn.password = CONFIG["connection"]["password"].asString();

        conn.keyspace = CONFIG["keyspace"].asString();
        conn.strategy = (EScyllaDbTopologyStrat::Enum)CONFIG["strategy"].asInt();
        conn.replication_factor = CONFIG["replication_factor"].asInt();

        IScyllaDb.initializeConstructor(conn);

        m_conn = conn;
    }
    ~CBaseDb()
    {
    }

    void cleanup()
    {
        std::string query = "drop table if exists {KEYSPACE}.{TABLE_NAME};";

        utilityFunctions::findAndReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::findAndReplaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        if (IScyllaDb.executeQuery(IScyllaDb.getCassSessionPtr(), query.c_str()) != CASS_OK)
        {
            IScyllaDb.printError(IScyllaDb.getCassFuturePtr(), "#2");
        }
    }

    void initialize()
    {
        std::string query = "create keyspace if not exists {KEYSPACE} with replication = { 'class': '{TOPOLOGY_STRATEGY}' };";

        utilityFunctions::findAndReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::findAndReplaceAll(query, "{TOPOLOGY_STRATEGY}", EScyllaDbTopologyStrat::toString(m_conn.strategy));

        if (IScyllaDb.executeQuery(IScyllaDb.getCassSessionPtr(), query.c_str()) != CASS_OK)
        {
            IScyllaDb.printError(IScyllaDb.getCassFuturePtr(), "#1");
        }

        cleanup();
    }

    void initializeType()
    {
        // n/a
    }
    void initializeTable()
    {
        std::string query = R"(create table if not exists {KEYSPACE}.{TABLE_NAME}
(
    id          uuid,
    time_text   text,

    primary key (id)
);)";
        utilityFunctions::findAndReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::findAndReplaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        if (IScyllaDb.executeQuery(IScyllaDb.getCassSessionPtr(), query.c_str()) != CASS_OK)
        {
            IScyllaDb.printError(IScyllaDb.getCassFuturePtr(), "#3");
        }
    }
    void alterizeCurrentTable()
    {
        // n/a
    }

    void generateUuidV4forCheck(int64_t errorCount, int64_t iterCount, int64_t collideCount, const int64_t &maxIter)
    {
        std::lock_guard<std::mutex> lock(printMutex);

        CUtilityModule UTILITY;

        std::string query = "insert into {KEYSPACE}.{TABLE_NAME} (id, time_text) values (uuid(), '{REPLACE_TIME_TEXT}') if not exists;";

        utilityFunctions::findAndReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::findAndReplaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        std::string currentTz = UTILITY.DateAndTime.UTC.TimeZone.toStringTZ();
        utilityFunctions::findAndReplaceAll(query, "{REPLACE_TIME_TEXT}", currentTz);

        size_t parameterCounts = 0;

        auto pStatement = cass_statement_new(query.c_str(), 0);

        auto pFuture = cass_session_execute(IScyllaDb.getCassSessionPtr(), pStatement);
        cass_future_wait(pFuture);

        auto status = cass_future_error_code(pFuture);

        if (status != CASS_OK)
        {
            errorCount += 1;
        }
        else
        {
            auto pResult = cass_future_get_result(pFuture);
            auto pFirstRow = cass_result_first_row(pResult);

            cass_bool_t applied;
            cass_value_get_bool(cass_row_get_column_by_name(pFirstRow, "[applied]"), &applied);

            if (!applied)
            {
                collideCount += 1;
            }

            cass_result_free(pResult);
        }

        if (iterCount < maxIter)
        {
            std::cout << "\r    \r";
            std::cout << "-- NOTE: current iter is " << iterCount+1 << " with " << errorCount << " error & " << collideCount << " collide" << std::flush;
        }

        if (iterCount == maxIter)
        {
            std::cout << "\n";
        }
        
        cass_statement_free(pStatement);
        cass_future_free(pFuture);
    }
};

///////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    // NOTE:
    // - copy config.debug.json to config.json
    // - replace CHANGE_ME with proper value of your system environment
    CBaseDb table;
    table.initialize();
    table.initializeType();
    table.initializeTable();
    table.alterizeCurrentTable();

    int64_t baseIter = 0;
    int64_t errorCount = 0;
    int64_t collideCount = 0;

    const int64_t MAX_ITER = 1000000;
    const int64_t NUM_THREADS = std::thread::hardware_concurrency();

    std::vector<std::future<void>> futures;

    auto start = std::chrono::high_resolution_clock::now();

    while (true)
    {
        baseIter++;

        futures.push_back(std::async(std::launch::async, &CBaseDb::generateUuidV4forCheck, &table, std::ref(errorCount), std::ref(baseIter), std::ref(collideCount), std::ref(MAX_ITER)));

        if (baseIter >= MAX_ITER)
        {
            std::cout << "\n-- NOTE: reaching iter max limit, stoping\n";
            break;
        }

        futures[baseIter - 1].get();
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    if (errorCount > 0 || collideCount > 0)
    {
        std::cout << "-- NOTE: found " << errorCount << " error & " << collideCount << " collide, while executing insertion in " << duration.count() << "seconds\n";
    }
    else
    {
        std::cout << "-- NOTE: no error & collide found in " << duration.count() << " seconds\n";
    }

    table.cleanup();
}
