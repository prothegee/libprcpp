#ifndef LIBPRCPP_SCYLLA_TYPES_HH
#define LIBPRCPP_SCYLLA_TYPES_HH
#include <libprcpp/enums/scylla_enums.hh>

namespace libprcpp
{

/**
 * @brief type for scylladb connection
 * 
 */
struct TScyllaDbConnection
{
    std::string host = "";
    std::string username = "";
    std::string password = "";
    std::string keyspace = "";
    EScyllaDbAuthMode auth_mode = EScyllaDbAuthMode::SCYLLADB_AUTH_MODE_UNDEFINED;
    EScyllaDbTopologyStrat strategy = EScyllaDbTopologyStrat::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;
    int replication_factor = 3;
};

} // namespace libprcpp

#endif // LIBPRCPP_SCYLLA_TYPES_HH
