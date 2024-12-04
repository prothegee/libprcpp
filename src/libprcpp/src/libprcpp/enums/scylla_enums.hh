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
    enum Enum : TInt32
    {
        SCYLLADB_AUTH_MODE_UNDEFINED = 0,
        SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR,
        SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR,
        SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR,
    };

    /**
     * @brief code for EScyllaAuthMode
     * 
     */
    struct Code
    {
        inline static const char *SCYLLADB_AUTH_MODE_UNDEFINED = "Undefined";
        inline static const char *SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR = "AllowAllAuthenticator";
        inline static const char *SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR = "PasswordAuthenticator";
        inline static const char *SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR = "com.scylladb.auth.TransitionalAuthenticator";
    };

    /**
     * @brief convert EScyllaAuthMode enum to string
     * 
     * @param authModeEnum 
     * @return std::string 
     */
    static std::string toString(const Enum &authModeEnum)
    {
        std::string result = Code::SCYLLADB_AUTH_MODE_UNDEFINED;

        switch (authModeEnum)
        {
            case Enum::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR:
            {
                result = Code::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR;
            }
            break;
            case Enum::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR:
            {
                result = Code::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR;
            }
            break;
            case Enum::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR:
            {
                result = Code::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR;
            }
            break;
            default:
            {
                result = Code::SCYLLADB_AUTH_MODE_UNDEFINED;
            }
            break;
        }

        return result;
    }

    /**
     * @brief convert EScyllaAuthMode string to enum
     * 
     * @param authModeString 
     * @return Enum 
     */
    static Enum toEnum(const char *&authModeString)
    {
        Enum result = Enum::SCYLLADB_AUTH_MODE_UNDEFINED;

        if (authModeString == Code::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR)
        {
            result = Enum::SCYLLADB_AUTH_MODE_ALLOW_ALL_AUTHENTICATOR;
        }
        else if (authModeString == Code::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR)
        {
            result = Enum::SCYLLADB_AUTH_MODE_PASSWORD_AUTHENTICATOR;
        }
        else if (authModeString == Code::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR)
        {
            result = Enum::SCYLLADB_AUTH_MODE_COM_SCYLLADB_AUTH_TRANSITIONAL_AUTHENTICATOR;
        }
        else
        {
            result = Enum::SCYLLADB_AUTH_MODE_UNDEFINED;
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
    enum Enum : TInt32
    {
        SCYLLADB_TOPOLOGY_STRAT_UNDEFINED = 0,
        SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY,
        SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY,
        SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY,
        SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY,
    };

    /**
     * @brief code for EScyllaDbTopologyStrat
     * 
     */
    struct Code
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
     * @param topologyStratEnum 
     * @return std::string 
     */
    static std::string toString(const Enum &topologyStratEnum)
    {
        std::string result = Code::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;

        switch (topologyStratEnum)
        {
            case Enum::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY:
            {
                result = Code::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY;
            }
            break;
            case Enum::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY:
            {
                result = Code::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY;
            }
            break;
            case Enum::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY:
            {
                result = Code::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY;
            }
            break;
            case Enum::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY:
            {
                result = Code::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY;
            }
            break;
            default:
            {
                result = Code::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;
            }
            break;
        }

        return result;
    }

    /**
     * @brief convert EScyllaDbTopologyStrat string to enum
     * 
     * @param topologyStratString 
     * @return Enum 
     */
    static Enum toEnum(const char *&topologyStratString)
    {
        Enum result = Enum::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;

        if (topologyStratString == Code::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY)
        {
            result = Enum::SCYLLADB_TOPOLOGY_STRAT_SIMPLE_STRATEGY;
        }
        else if (topologyStratString == Code::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY)
        {
            result = Enum::SCYLLADB_TOPOLOGY_STRAT_NETWORK_TOPOLOGY_STRATEGY;
        }
        else if (topologyStratString == Code::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY)
        {
            result = Enum::SCYLLADB_TOPOLOGY_STRAT_LOCAL_STRATEGY;
        }
        else if (topologyStratString == Code::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY)
        {
            result = Enum::SCYLLADB_TOPOLOGY_STRAT_EVERYWHERE_STRATEGY;
        }
        else
        {
            result = Enum::SCYLLADB_TOPOLOGY_STRAT_UNDEFINED;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_SCYLLADB_ENUMS_HH
