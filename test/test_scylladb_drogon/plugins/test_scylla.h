#ifndef TEST_SCYLLADB_DROGON_TEST_SCYLLA_H
#define TEST_SCYLLADB_DROGON_TEST_SCYLLA_H
#include <drogon/drogon.h>

#include <libprcpp/interfaces/iscylladb_core_interface.h>

namespace test_scylladb_drogon
{

using namespace drogon;
using namespace libprcpp;

// test scylla class
class CTestScylla final : public IScyllaDbCoreInterface
{
public:
    CTestScylla();
    ~CTestScylla();

    void initializeType();
    void initializeTable();
    void alterizeCurrentTable();

    void initializeKeyspaceProject();
};

} // namespace test_scylladb_drogon

#endif // #define TEST_SCYLLADB_DROGON_TEST_SCYLLA_H