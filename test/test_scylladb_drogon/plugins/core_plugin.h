#ifndef TEST_SCYLLADB_DROGON_CORE_PLUGIN_H
#define TEST_SCYLLADB_DROGON_CORE_PLUGIN_H
#include <drogon/drogon.h>

namespace test_scylladb_drogon
{

using namespace drogon;

// core plugin calass
class CCorePlugin  final : public Plugin<CCorePlugin>
{
private:
    /* data */

protected:
    void initAndStart(const Json::Value &config);
    void shutdown();

public:
    CCorePlugin(/* args */);
    ~CCorePlugin();
};

} // namespace test_scylladb_drogon

#endif // TEST_SCYLLADB_DROGON_CORE_PLUGIN_H
