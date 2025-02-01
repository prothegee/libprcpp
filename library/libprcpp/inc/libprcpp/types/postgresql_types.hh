#ifndef LIBPRCPP_POSTGRESQL_TYPES_HH
#define LIBPRCPP_POSTGRESQL_TYPES_HH
#include <string>

namespace libprcpp
{

struct TPostgreSQLConnection
{
    std::string dbname = "";
    std::string host = "";
    std::string port = "";
    std::string username = "";
    std::string password = "";
};

} // namespace libprcpp

#endif // LIBPRCPP_POSTGRESQL_TYPES_HH
