#include <libprcpp/interfaces/iscylladb_core_interface.hh>
#include <libprcpp/functions/utility_funcs.hh>
#include <libprcpp/functions/date_and_times_funcs.hh>

using namespace libprcpp;

//////////////////////////////////////////////


#if LIBPRCPP_USING_SCYLLADB
std::mutex printMutex;
class CScyllaDbCase : public IScyllaDbCoreInterface
{
private:
    TScyllaDbConnection m_conn;

    const std::string TABLE_NAME = "tb_uuidv4_collide";

public:
    CScyllaDbCase(/* args */)
    {
        const auto CONFIG = utilityFunctions::json::fromFile("../../../../test/test_libprcpp/test_libprcpp_scylladb.json");

        TScyllaDbConnection conn;

        conn.auth_mode = (EScyllaDbAuthMode)CONFIG["connection"]["auth"].asInt();
        conn.host = CONFIG["connection"]["hosts"].asString();
        conn.username = CONFIG["connection"]["username"].asString();
        conn.password = CONFIG["connection"]["password"].asString();

        conn.keyspace = CONFIG["keyspace"].asString();
        conn.strategy = (EScyllaDbTopologyStrat)CONFIG["strategy"].asInt();
        conn.replication_factor = CONFIG["replication_factor"].asInt();

        IScyllaDb.initializeConstructor(conn);

        m_conn = conn;
    }
    ////////////////////////////////////////
    ~CScyllaDbCase()
    {
    }

    ////////////////////////////////////////

    void initialize()
    {
        std::string query = "create keyspace if not exists {KEYSPACE} with replication = { 'class': '{TOPOLOGY_STRATEGY}' };";

        utilityFunctions::find::andReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::find::andReplaceAll(query, "{TOPOLOGY_STRATEGY}", EScyllaDbTopologyStratToString(m_conn.strategy));

        if (IScyllaDb.executeQuery(IScyllaDb.getCassSessionPtr(), query.c_str()) != CASS_OK)
        {
            IScyllaDb.printError(IScyllaDb.getCassFuturePtr(), "#1");
        }

        cleanup();
    }

    void initializeType()
    {
        std::cout << "SKIPPED: CScyllaDbCase::initializeType n/a\n";
    }
    void initializeTable()
    {
        std::string query = R"(create table if not exists {KEYSPACE}.{TABLE_NAME}
(
    id          uuid,
    time_text   text,

    primary key (id)
);)";
        utilityFunctions::find::andReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::find::andReplaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        if (IScyllaDb.executeQuery(IScyllaDb.getCassSessionPtr(), query.c_str()) != CASS_OK)
        {
            IScyllaDb.printError(IScyllaDb.getCassFuturePtr(), "#3");
        }
    }
    void initializeIndex()
    {
        std::cout << "SKIPPED: CScyllaDbCase::initializeIndex n/a\n";
    }
    void alterizeCurrentTable()
    {
        std::cout << "SKIPPED: CScyllaDbCase::alterizeCurrentTable n/a\n";
    }
    void alterizeMaterializedView()
    {
        std::cout << "SKIPPED: CScyllaDbCase::alterizeMaterializedView n/a\n";
    }

    void generateUuidV4forCheck(int64_t errorCount, int64_t iterCount, int64_t collideCount, const int64_t &maxIter)
    {
        std::lock_guard<std::mutex> lock(printMutex);

        std::string query = "insert into {KEYSPACE}.{TABLE_NAME} (id, time_text) values (uuid(), '{REPLACE_TIME_TEXT}') if not exists;";

        utilityFunctions::find::andReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::find::andReplaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        std::string currentTz = dateAndTimesFunctions::UTC::timeZone::toString();

        utilityFunctions::find::andReplaceAll(query, "{REPLACE_TIME_TEXT}", currentTz);

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

    void cleanup()
    {
        std::string query = "drop table if exists {KEYSPACE}.{TABLE_NAME};";

        utilityFunctions::find::andReplaceAll(query, "{KEYSPACE}", m_conn.keyspace);
        utilityFunctions::find::andReplaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        if (IScyllaDb.executeQuery(IScyllaDb.getCassSessionPtr(), query.c_str()) != CASS_OK)
        {
            IScyllaDb.printError(IScyllaDb.getCassFuturePtr(), "#2");
        }
    }
};
#endif // LIBPRCPP_USING_SCYLLADB


//////////////////////////////////////////////


int main()
{
#if LIBPRCPP_USING_SCYLLADB
    CScyllaDbCase table;
    table.initialize();
    table.initializeType();
    table.initializeTable();
    table.alterizeCurrentTable();

    int64_t baseIter = 0;
    int64_t errorCount = 0;
    int64_t collideCount = 0;

    const int64_t MAX_ITER = 100;
    const int64_t NUM_THREADS = std::thread::hardware_concurrency();

    std::vector<std::future<void>> futures;

    auto start = std::chrono::high_resolution_clock::now();

    while (true)
    {
        baseIter++;

        futures.push_back(std::async(std::launch::async, &CScyllaDbCase::generateUuidV4forCheck, &table, std::ref(errorCount), std::ref(baseIter), std::ref(collideCount), std::ref(MAX_ITER)));

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
#endif // LIBPRCPP_USING_SCYLLADB

    return 0;
}
