#include <drogon/drogon.h>

using namespace drogon;

int main(int argc, char *argv[])
{
    app().loadConfigFile("../../../test/test_scylladb_drogon/config.json");

    // check plugin to excute scylladb

    app().run();
}
