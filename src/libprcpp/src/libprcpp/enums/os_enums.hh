#ifndef LIBPRCPP_OS_ENUMS_HH
#define LIBPRCPP_OS_ENUMS_HH
#include <libprcpp/types/basic_types.hh>

namespace libprcpp
{

/**
 * @brief enum os environment structure
 * 
 */
struct EOSEnvironment
{
    /**
     * @brief enum object for EOSEnvironment
     * 
     */
    enum ENUM : TInt32
    {
        OS_ENVIRONMENT_UNDEFINED = 0,
        OS_ENVIRONMENT_DESKTOP,
        OS_ENVIRONMENT_MOBILE,
    };

    /**
     * @brief code object for EOSEnvironment
     * 
     */
    struct CODE
    {
        inline static const char *OS_ENVIRONMENT_UNDEFINED = "Undefined";
        inline static const char *OS_ENVIRONMENT_DESKTOP = "Desktop";
        inline static const char *OS_ENVIRONMENT_MOBILE = "Mobile";
    };

    /**
     * @brief convert EOSEnvironment enum to string
     * 
     * @param osTypeENUM 
     * @return std::string 
     */
    static std::string toString(const ENUM &osEnvironmentENUM)
    {
        std::string result = CODE::OS_ENVIRONMENT_UNDEFINED;

        switch (osEnvironmentENUM)
        {
            case ENUM::OS_ENVIRONMENT_DESKTOP: { result = CODE::OS_ENVIRONMENT_DESKTOP; } break;
            case ENUM::OS_ENVIRONMENT_MOBILE: { result = CODE::OS_ENVIRONMENT_MOBILE; } break;
            default: { result = CODE::OS_ENVIRONMENT_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief convert EOSEnvironment string to enum
     * 
     * @param osEnvironmentString 
     * @return ENUM 
     */
    static ENUM toENUM(const char *&osEnvironmentString)
    {
        ENUM result = ENUM::OS_ENVIRONMENT_UNDEFINED;

        if (osEnvironmentString == CODE::OS_ENVIRONMENT_DESKTOP)
        {
            result = ENUM::OS_ENVIRONMENT_DESKTOP;
        }
        else if (osEnvironmentString == CODE::OS_ENVIRONMENT_MOBILE)
        {
            result = ENUM::OS_ENVIRONMENT_MOBILE;
        }
        else
        {
            result = ENUM::OS_ENVIRONMENT_UNDEFINED;
        }

        return result;
    }

    /**
     * @brief get OS environment string
     * 
     * @return std::string 
     */
    static std::string getCurrentOSEnvironmentToString()
    {
        std::string result = CODE::OS_ENVIRONMENT_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = CODE::OS_ENVIRONMENT_DESKTOP; } break;
            case 2: { result = CODE::OS_ENVIRONMENT_DESKTOP; } break;
            case 3: { result = CODE::OS_ENVIRONMENT_DESKTOP; } break;
            case 4: { result = CODE::OS_ENVIRONMENT_MOBILE; } break;
            case 5: { result = CODE::OS_ENVIRONMENT_MOBILE; } break;
            default: { result = CODE::OS_ENVIRONMENT_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief get OS environment enum
     * 
     * @return ENUM 
     */
    static ENUM getCurrentOSEnvironmentToENUM()
    {
        ENUM result = ENUM::OS_ENVIRONMENT_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = ENUM::OS_ENVIRONMENT_DESKTOP; } break;
            case 2: { result = ENUM::OS_ENVIRONMENT_DESKTOP; } break;
            case 3: { result = ENUM::OS_ENVIRONMENT_DESKTOP; } break;
            case 4: { result = ENUM::OS_ENVIRONMENT_MOBILE; } break;
            case 5: { result = ENUM::OS_ENVIRONMENT_MOBILE; } break;
            default: { result = ENUM::OS_ENVIRONMENT_UNDEFINED; } break;
        }

        return result;
    }
};

/**
 * @brief enum os type structure
 * 
 */
struct EOSType
{
    /**
     * @brief enum object for EOSType
     * 
     */
    enum ENUM : TInt32
    {
        OS_TYPE_UNDEFINED = 0,
        OS_TYPE_LINUX,
        OS_TYPE_WINDOWS,
        OS_TYPE_MACOS,
        OS_TYPE_ANDROID,
        OS_TYPE_IOS,
    };

    /**
     * @brief code object for EOSType
     * 
     */
    struct CODE
    {
        inline static const char *OS_TYPE_UNDEFINED = "Undefined";
        inline static const char *OS_TYPE_LINUX = "Linux";
        inline static const char *OS_TYPE_WINDOWS = "Windows";
        inline static const char *OS_TYPE_MACOS = "MacOS";
        inline static const char *OS_TYPE_ANDROID = "Android";
        inline static const char *OS_TYPE_IOS = "IOS";
    };

    /**
     * @brief convert EOSType enum to string
     * 
     * @param osTypeENUM 
     * @return std::string 
     */
    static std::string toString(const ENUM &osTypeENUM)
    {
        std::string result = CODE::OS_TYPE_UNDEFINED;

        switch (osTypeENUM)
        {
            case ENUM::OS_TYPE_LINUX: { result = CODE::OS_TYPE_LINUX; } break;
            case ENUM::OS_TYPE_WINDOWS: { result = CODE::OS_TYPE_WINDOWS; } break;
            case ENUM::OS_TYPE_MACOS: { result = CODE::OS_TYPE_MACOS; } break;
            case ENUM::OS_TYPE_ANDROID: { result = CODE::OS_TYPE_ANDROID; } break;
            case ENUM::OS_TYPE_IOS: { result = CODE::OS_TYPE_IOS; } break;
            default: { result = CODE::OS_TYPE_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief convert EOSType string to enum
     * 
     * @param osTypeString 
     * @return ENUM 
     */
    static ENUM toENUM(const char *&osTypeString)
    {
        ENUM result = ENUM::OS_TYPE_UNDEFINED;

        if (osTypeString == CODE::OS_TYPE_LINUX)
        {
            result = ENUM::OS_TYPE_LINUX;
        }
        else if (osTypeString == CODE::OS_TYPE_WINDOWS)
        {
            result = ENUM::OS_TYPE_WINDOWS;
        }
        else if (osTypeString == CODE::OS_TYPE_MACOS)
        {
            result = ENUM::OS_TYPE_MACOS;
        }
        else if (osTypeString == CODE::OS_TYPE_ANDROID)
        {
            result = ENUM::OS_TYPE_ANDROID;
        }
        else if (osTypeString == CODE::OS_TYPE_IOS)
        {
            result = ENUM::OS_TYPE_IOS;
        }
        else
        {
            result = ENUM::OS_TYPE_UNDEFINED;
        }

        return result;
    }

    /**
     * @brief get OS name string
     * 
     * @return std::string 
     */
    static std::string getCurrentOSNameToString()
    {
        std::string result = CODE::OS_TYPE_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = CODE::OS_TYPE_LINUX; } break;
            case 2: { result = CODE::OS_TYPE_WINDOWS; } break;
            case 3: { result = CODE::OS_TYPE_MACOS; } break;
            case 4: { result = CODE::OS_TYPE_ANDROID; } break;
            case 5: { result = CODE::OS_TYPE_IOS; } break;
            default: { result = CODE::OS_TYPE_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief get OS name enum
     * 
     * @return ENUM 
     */
    static ENUM getCurrentOSNameToENUM()
    {
        ENUM result = ENUM::OS_TYPE_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = ENUM::OS_TYPE_LINUX; } break;
            case 2: { result = ENUM::OS_TYPE_WINDOWS; } break;
            case 3: { result = ENUM::OS_TYPE_MACOS; } break;
            case 4: { result = ENUM::OS_TYPE_ANDROID; } break;
            case 5: { result = ENUM::OS_TYPE_IOS; } break;
            default: { result = ENUM::OS_TYPE_UNDEFINED; } break;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_OS_ENUMS_HH
