#ifndef LIBPRCPP_OS_ENUMS_H
#define LIBPRCPP_OS_ENUMS_H
#include <libprcpp/types/basic_types.h>

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
    enum Enum : TInt32
    {
        OS_ENVIRONMENT_UNDEFINED = 0,
        OS_ENVIRONMENT_DESKTOP,
        OS_ENVIRONMENT_MOBILE,
    };

    /**
     * @brief code object for EOSEnvironment
     * 
     */
    struct Code
    {
        inline static const std::string OS_ENVIRONMENT_UNDEFINED = "Undefined";
        inline static const std::string OS_ENVIRONMENT_DESKTOP = "Desktop";
        inline static const std::string OS_ENVIRONMENT_MOBILE = "Mobile";
    };

    /**
     * @brief convert EOSEnvironment enum to string
     * 
     * @param osTypeEnum 
     * @return std::string 
     */
    static std::string toString(const Enum &osEnvironmentEnum)
    {
        std::string result = Code::OS_ENVIRONMENT_UNDEFINED;

        switch (osEnvironmentEnum)
        {
            case Enum::OS_ENVIRONMENT_DESKTOP: { result = Code::OS_ENVIRONMENT_DESKTOP; } break;
            case Enum::OS_ENVIRONMENT_MOBILE: { result = Code::OS_ENVIRONMENT_MOBILE; } break;
            default: { result = Code::OS_ENVIRONMENT_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief convert EOSEnvironment string to enum
     * 
     * @param osEnvironmentString 
     * @return Enum 
     */
    static Enum toEnum(const std::string &osEnvironmentString)
    {
        Enum result = Enum::OS_ENVIRONMENT_UNDEFINED;

        if (osEnvironmentString == Code::OS_ENVIRONMENT_DESKTOP)
        {
            result = Enum::OS_ENVIRONMENT_DESKTOP;
        }
        else if (osEnvironmentString == Code::OS_ENVIRONMENT_MOBILE)
        {
            result = Enum::OS_ENVIRONMENT_MOBILE;
        }
        else
        {
            result = Enum::OS_ENVIRONMENT_UNDEFINED;
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
        std::string result = Code::OS_ENVIRONMENT_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = Code::OS_ENVIRONMENT_DESKTOP; } break;
            case 2: { result = Code::OS_ENVIRONMENT_DESKTOP; } break;
            case 3: { result = Code::OS_ENVIRONMENT_DESKTOP; } break;
            case 4: { result = Code::OS_ENVIRONMENT_MOBILE; } break;
            case 5: { result = Code::OS_ENVIRONMENT_MOBILE; } break;
            default: { result = Code::OS_ENVIRONMENT_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief get OS environment enum
     * 
     * @return Enum 
     */
    static Enum getCurrentOSEnvironmentToEnum()
    {
        Enum result = Enum::OS_ENVIRONMENT_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = Enum::OS_ENVIRONMENT_DESKTOP; } break;
            case 2: { result = Enum::OS_ENVIRONMENT_DESKTOP; } break;
            case 3: { result = Enum::OS_ENVIRONMENT_DESKTOP; } break;
            case 4: { result = Enum::OS_ENVIRONMENT_MOBILE; } break;
            case 5: { result = Enum::OS_ENVIRONMENT_MOBILE; } break;
            default: { result = Enum::OS_ENVIRONMENT_UNDEFINED; } break;
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
    enum Enum : TInt32
    {
        OS_TYPE_UNDEFINED = 0,
        OS_TYPE_LINUX,
        OS_TYPE_WINDOWS,
        OS_TYPE_OSX,
        OS_TYPE_ANDROID,
        OS_TYPE_IOS,
    };

    /**
     * @brief code object for EOSType
     * 
     */
    struct Code
    {
        inline static const std::string OS_TYPE_UNDEFINED = "Undefined";
        inline static const std::string OS_TYPE_LINUX = "Linux";
        inline static const std::string OS_TYPE_WINDOWS = "Windows";
        inline static const std::string OS_TYPE_OSX = "OSX";
        inline static const std::string OS_TYPE_ANDROID = "Android";
        inline static const std::string OS_TYPE_IOS = "IOS";
    };

    /**
     * @brief convert EOSType enum to string
     * 
     * @param osTypeEnum 
     * @return std::string 
     */
    static std::string toString(const Enum &osTypeEnum)
    {
        std::string result = Code::OS_TYPE_UNDEFINED;

        switch (osTypeEnum)
        {
            case Enum::OS_TYPE_LINUX: { result = Code::OS_TYPE_LINUX; } break;
            case Enum::OS_TYPE_WINDOWS: { result = Code::OS_TYPE_WINDOWS; } break;
            case Enum::OS_TYPE_OSX: { result = Code::OS_TYPE_OSX; } break;
            case Enum::OS_TYPE_ANDROID: { result = Code::OS_TYPE_ANDROID; } break;
            case Enum::OS_TYPE_IOS: { result = Code::OS_TYPE_IOS; } break;
            default: { result = Code::OS_TYPE_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief convert EOSType string to enum
     * 
     * @param osTypeString 
     * @return Enum 
     */
    static Enum toEnum(const std::string &osTypeString)
    {
        Enum result = Enum::OS_TYPE_UNDEFINED;

        if (osTypeString == Code::OS_TYPE_LINUX)
        {
            result = Enum::OS_TYPE_LINUX;
        }
        else if (osTypeString == Code::OS_TYPE_WINDOWS)
        {
            result = Enum::OS_TYPE_WINDOWS;
        }
        else if (osTypeString == Code::OS_TYPE_OSX)
        {
            result = Enum::OS_TYPE_OSX;
        }
        else if (osTypeString == Code::OS_TYPE_ANDROID)
        {
            result = Enum::OS_TYPE_ANDROID;
        }
        else if (osTypeString == Code::OS_TYPE_IOS)
        {
            result = Enum::OS_TYPE_IOS;
        }
        else
        {
            result = Enum::OS_TYPE_UNDEFINED;
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
        std::string result = Code::OS_TYPE_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = Code::OS_TYPE_LINUX; } break;
            case 2: { result = Code::OS_TYPE_WINDOWS; } break;
            case 3: { result = Code::OS_TYPE_OSX; } break;
            case 4: { result = Code::OS_TYPE_ANDROID; } break;
            case 5: { result = Code::OS_TYPE_IOS; } break;
            default: { result = Code::OS_TYPE_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief get OS name enum
     * 
     * @return Enum 
     */
    static Enum getCurrentOSNameToEnum()
    {
        Enum result = Enum::OS_TYPE_UNDEFINED;

        switch (PROJECT_BUILD_TARGET)
        {
            case 1: { result = Enum::OS_TYPE_LINUX; } break;
            case 2: { result = Enum::OS_TYPE_WINDOWS; } break;
            case 3: { result = Enum::OS_TYPE_OSX; } break;
            case 4: { result = Enum::OS_TYPE_ANDROID; } break;
            case 5: { result = Enum::OS_TYPE_IOS; } break;
            default: { result = Enum::OS_TYPE_UNDEFINED; } break;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_OS_ENUMS_H
