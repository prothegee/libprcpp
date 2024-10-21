#include "test_scylla.hh"

namespace test_scylladb_drogon
{

CTestScylla::CTestScylla()
{
    auto config_auth_mode = app().getCustomConfig()["integration"]["db"]["scylladb"]["connection"]["auth"].asInt();

    TScyllaDbConnection conn;

    conn.host = app().getCustomConfig()["integration"]["db"]["scylladb"]["connection"]["hosts"].asString();
    conn.username = app().getCustomConfig()["integration"]["db"]["scylladb"]["connection"]["username"].asString();
    conn.password = app().getCustomConfig()["integration"]["db"]["scylladb"]["connection"]["password"].asString();
    conn.auth_mode = (EScyllaDbAuthMode::Enum)app().getCustomConfig()["integration"]["db"]["scylladb"]["connection"]["auth"].asInt();

    conn.keyspace = app().getCustomConfig()["integration"]["db"]["scylladb"]["keyspace"].asString();
    conn.replication_factor = app().getCustomConfig()["integration"]["db"]["scylladb"]["replication_factor"].asInt();
    conn.strategy = (EScyllaDbTopologyStrat::Enum)app().getCustomConfig()["integration"]["db"]["scylladb"]["strategy"].asInt();

    std::cout << "scylladb connection info:\n";
    std::cout << "host: " << conn.host << "\n";
    std::cout << "username: " << conn.username << "\n";
    std::cout << "password: " << conn.password << "\n";
    std::cout << "auth_mode: " << EScyllaDbAuthMode::toString(conn.auth_mode) << "\n"; // why this one is Undefined?
    std::cout << "keyspace: " << conn.keyspace << "\n";
    std::cout << "replication_factor: " << conn.replication_factor << "\n";
    std::cout << "strategy: " << EScyllaDbTopologyStrat::toString(conn.strategy) << "\n";
    std::cout << "config_auth_mode: " << config_auth_mode << "\n";

    IScyllaDb.initializeConstructor(conn);
}

CTestScylla::~CTestScylla()
{
}

void CTestScylla::initializeType()
{
    std::cout << "MESSAGE: call \"CTestScylla::initializeType\"\n";
}

void CTestScylla::initializeTable()
{
    std::cout << "MESSAGE: call \"CTestScylla::initializeTable\"\n";
}

void CTestScylla::initializeIndex()
{
    std::cout << "MESSAGE: call \"CTestScylla::initializeIndex\"\n";
}

void CTestScylla::alterizeCurrentTable()
{
    std::cout << "MESSAGE: call \"CTestScylla::alterizeCurrentTable\"\n";
}

void CTestScylla::alterizeMaterializedView()
{
    std::cout << "MESSAGE: call \"CTestScylla::alterizeMaterializedView\"\n";
}

void CTestScylla::initializeKeyspaceProject()
{
    std::cout << "MESSAGE: call \"CTestScylla::initializeKeyspaceProject\"\n";

    std::string query = "describe keyspaces;";

    if (IScyllaDb.executeQuery(IScyllaDb.getCassSessionPtr(), query.c_str()) == CASS_OK)
    {
        std::cout << "MESSAGE: excuting \"describe keyspaces;\"\n";
    }
    else
    {
        std::cout << "MESSAGE: can't excuting \"describe keyspaces;\"\n";
    }
}

} // namespace test_scylladb_drogon
