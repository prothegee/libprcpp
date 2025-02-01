#ifndef TEST_SCYLLADB_DROGON_TEST_SCYLLA_HH
#define TEST_SCYLLADB_DROGON_TEST_SCYLLA_HH
#include <drogon/drogon.h>

#include <libprcpp/interfaces/iscylladb_core_interface.hh>

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
    void initializeIndex();
    void alterizeCurrentTable();
    void alterizeMaterializedView();

    void initializeKeyspaceProject();
};

} // namespace test_scylladb_drogon

#endif // #define TEST_SCYLLADB_DROGON_TEST_SCYLLA_HH