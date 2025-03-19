#ifndef LIBPRCPP_SCYLLADB_ENUMS_HH
#define LIBPRCPP_SCYLLADB_ENUMS_HH
#include <libprcpp/types/base_types.hh>

namespace libprcpp
{


/**
 * @brief scylladb auth mode enum
 */
enum EScyllaDbAuthMode : TI32
{
    SCYLLADB_AUTH_MODE_UNDEFINED,
    SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR,
    SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR,
    SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR,
};

inline static const TChr *SCYLLADB_AUTH_MODE_UNDEFINED_HINT                                      = "Undefined"; // Undefined
inline static const TChr *SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR_HINT                        = "AllowAllAuthenticator"; // AllowAllAuthenticator
inline static const TChr *SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR_HINT                         = "PasswordAuthenticator"; // PasswordAuthenticator
inline static const TChr *SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR_HINT   = "com.scylladb.auth.TransitionalAuthenticator"; // com.scylladb.auth.TransitionalAuthenticator

/**
 * @brief get string value of related scylladbAuthModeEnum
 * 
 * @param scylladbAuthModeEnum 
 * @return const TChr* 
 */
inline static const TChr *EScyllaDbAuthModeToString(const EScyllaDbAuthMode &scylladbAuthModeEnum)
{
    switch (scylladbAuthModeEnum)
    {
        case SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR:                        { return SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR_HINT; } break;
        case SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR:                         { return SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR_HINT; } break;
        case SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR:   { return SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR_HINT; } break;
        default:                                                                { return SCYLLADB_AUTH_MODE_UNDEFINED_HINT; } break;
    }
}

/**
 * @brief get enum value of related scylladbAuthModeString
 * 
 * @param scylladbAuthModeString 
 * @return EScyllaDbAuthMode 
 */
inline static EScyllaDbAuthMode EScyllaDbAuthModeToEnum(const TChr *scylladbAuthModeString)
{
    if (scylladbAuthModeString == SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR_HINT)                      { return SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR; }
    if (scylladbAuthModeString == SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR_HINT)                       { return SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR; }
    if (scylladbAuthModeString == SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR_HINT) { return SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR; }
    return SCYLLADB_AUTH_MODE_UNDEFINED;
}


////////////////////////////////////////////////////////////////////////


/**
 * @brief scylladb topology strategy enum
 */
enum EScyllaDbTopologyStrat : TI32
{
    SCYLLADB_TOPOLOGY_STRAT_UNDEFINED,
    SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY,
    SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY,
    SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY,
    SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY,
};

inline static const TChr *SCYLLADB_TOPOLOGY_STRAT_UNDEFINED_HINT                 = "Undefined"; // Undefined
inline static const TChr *SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY_HINT           = "SimpleStrategy"; // SimpleStrategy
inline static const TChr *SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY_HINT = "NetworkTopologyStrategy"; // NetworkTopologyStrategy
inline static const TChr *SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY_HINT            = "LocalStrategy"; // LocalStrategy
inline static const TChr *SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY_HINT       = "EverywhereStrategy"; // EverywhereStrategy

/**
 * @brief get string value of related scylladbTopologyStratEnum
 * 
 * @param scylladbTopologyStratEnum 
 * @return const TChr* 
 */
inline static const TChr *EScyllaDbTopologyStratToString(const EScyllaDbTopologyStrat &scylladbTopologyStratEnum)
{
    switch (scylladbTopologyStratEnum)
    {
        case SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY:           { return SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY_HINT; } break;
        case SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY: { return SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY_HINT; } break;
        case SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY:            { return SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY_HINT; } break;
        case SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY:       { return SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY_HINT; } break;
        default:                                                { return SCYLLADB_TOPOLOGY_STRAT_UNDEFINED_HINT; } break;
    }
}

/**
 * @brief get enum value of related scyllaDbTopologyStratString
 * 
 * @param scyllaDbTopologyStratString 
 * @return EScyllaDbTopologyStrat 
 */
inline static EScyllaDbTopologyStrat EScyllaDbTopologyStratToEnum(const TChr *scyllaDbTopologyStratString)
{
    if (scyllaDbTopologyStratString == SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY_HINT)            { return SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY; }
    if (scyllaDbTopologyStratString == SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY_HINT)  { return SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY; }
    if (scyllaDbTopologyStratString == SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY_HINT)             { return SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY; }
    if (scyllaDbTopologyStratString == SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY_HINT)        { return SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY; }
    return SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;
}


} // namespace libprcpp

#endif // LIBPRCPP_SCYLLADB_ENUMS_HH
