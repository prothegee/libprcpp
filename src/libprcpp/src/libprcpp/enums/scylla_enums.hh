#ifndef LIBPRCPP_SCYLLADB_ENUMS_HH
#define LIBPRCPP_SCYLLADB_ENUMS_HH
#include <libprcpp/types/basic_types.hh>

namespace libprcpp
{

/**
 * @brief scylladb auth mode enum structure
 * 
 */
struct EScyllaDbAuthMode
{
    /**
     * @brief enum for EScyllaAuthMode
     * 
     */
    enum ENUM : TInt32
    {
        SCYLLADB_AUTH_MODE_UNDEFINED,
        SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR,
        SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR,
        SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR,
    };

    /**
     * @brief code for EScyllaAuthMode
     * 
     */
    struct CODE
    {
        inline static const char *SCYLLADB_AUTH_MODE_UNDEFINED = "Undefined";
        inline static const char *SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR = "AllowAllAuthenticator";
        inline static const char *SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR = "PasswordAuthenticator";
        inline static const char *SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR = "com.scylladb.auth.TransitionalAuthenticator";
    };

    /**
     * @brief convert EScyllaAuthMode enum to string
     * 
     * @param authModeENUM 
     * @return std::string 
     */
    static std::string toString(const ENUM &authModeENUM)
    {
        std::string result = CODE::SCYLLADB_AUTH_MODE_UNDEFINED;

        switch (authModeENUM)
        {
            case ENUM::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR:
            {
                result = CODE::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR;
            }
            break;
            case ENUM::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR:
            {
                result = CODE::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR;
            }
            break;
            case ENUM::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR:
            {
                result = CODE::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR;
            }
            break;
            default:
            {
                result = CODE::SCYLLADB_AUTH_MODE_UNDEFINED;
            }
            break;
        }

        return result;
    }

    /**
     * @brief convert EScyllaAuthMode string to enum
     * 
     * @param authModeString 
     * @return ENUM 
     */
    static ENUM toENUM(const char *&authModeString)
    {
        ENUM result = ENUM::SCYLLADB_AUTH_MODE_UNDEFINED;

        if (authModeString == CODE::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR)
        {
            result = ENUM::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR;
        }
        else if (authModeString == CODE::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR)
        {
            result = ENUM::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR;
        }
        else if (authModeString == CODE::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR)
        {
            result = ENUM::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR;
        }
        else
        {
            result = ENUM::SCYLLADB_AUTH_MODE_UNDEFINED;
        }

        return result;
    }
};

/**
 * @brief scylladb topology strategy enum structure
 * 
 */
struct EScyllaDbTopologyStrat
{
    /**
     * @brief enum for EScyllaDbTopologyStrat
     * 
     */
    enum ENUM : TInt32
    {
        SCYLLADB_TOPOLOGY_STRAT_UNDEFINED,
        SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY,
        SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY,
        SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY,
        SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY,
    };

    /**
     * @brief code for EScyllaDbTopologyStrat
     * 
     */
    struct CODE
    {
        inline static const char *SCYLLADB_TOPOLOGY_STRAT_UNDEFINED = "Undefined";
        inline static const char *SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY = "SimpleStrategy";
        inline static const char *SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY = "NetworkTopologyStrategy";
        inline static const char *SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY = "LocalStrategy";
        inline static const char *SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY = "EverywhereStrategy";
    };

    /**
     * @brief convert EScyllaDbTopologyStrat enum to string
     * 
     * @param topologyStratENUM 
     * @return std::string 
     */
    static std::string toString(const ENUM &topologyStratENUM)
    {
        std::string result = CODE::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;

        switch (topologyStratENUM)
        {
            case ENUM::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY:
            {
                result = CODE::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY;
            }
            break;
            case ENUM::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY:
            {
                result = CODE::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY;
            }
            break;
            case ENUM::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY:
            {
                result = CODE::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY;
            }
            break;
            case ENUM::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY:
            {
                result = CODE::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY;
            }
            break;
            default:
            {
                result = CODE::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;
            }
            break;
        }

        return result;
    }

    /**
     * @brief convert EScyllaDbTopologyStrat string to enum
     * 
     * @param topologyStratString 
     * @return ENUM 
     */
    static ENUM toENUM(const char *&topologyStratString)
    {
        ENUM result = ENUM::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;

        if (topologyStratString == CODE::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY)
        {
            result = ENUM::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY;
        }
        else if (topologyStratString == CODE::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY)
        {
            result = ENUM::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY;
        }
        else if (topologyStratString == CODE::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY)
        {
            result = ENUM::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY;
        }
        else if (topologyStratString == CODE::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY)
        {
            result = ENUM::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY;
        }
        else
        {
            result = ENUM::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_SCYLLADB_ENUMS_HH
