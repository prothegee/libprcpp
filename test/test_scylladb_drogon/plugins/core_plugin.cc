#include "core_plugin.hh"

#include "test_scylla.hh"

namespace test_scylladb_drogon
{

void CCorePlugin::initAndStart(const Json::Value &config)
{
    std::cout << "MESSAGE: test_scylladb_drogon::CCorePlugin::initAndStart\n";

    // test case
    CTestScylla db;
    db.initializeType();
    db.initializeTable();
    db.alterizeCurrentTable();
    db.initializeKeyspaceProject();

    std::cout << "MESSAGE: exiting test_scylladb_drogon after 1.5s\n";
    app().getLoop()->runAfter(1.5, []
    {
        app().quit();
    });
}

void CCorePlugin::shutdown()
{
    std::cout << "MESSAGE: test_scylladb_drogon::CCorePlugin::shutdown\n";
}

CCorePlugin::CCorePlugin()
{
}

CCorePlugin::~CCorePlugin()
{
}

} // namespace test_scylladb_drogon
