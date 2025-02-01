#ifndef LIBPRCPP_BUILD_ENUMS_HH
#define LIBPRCPP_BUILD_ENUMS_HH
#include <string>

namespace libprcpp
{

/**
 * @brief enum build target structure
 * 
 */
struct EBuildTarget
{
    /**
     * @brief enum object for EBuildTarget
     * 
     */
    enum ENUM
    {
        BUILD_TARGET_UNDEFINED,
        BUILD_TARGET_LINUX,
        BUILD_TARGET_WINDOWS,
        BUILD_TARGET_MACOS,
        BUILD_TARGET_ANDROID,
        BUILD_TARGET_IOS,
        BUILD_TARGET_WEB,
        BUILD_TARGET_PS,
        BUILD_TARGET_XBOX,
        BUILD_TARGET_NINTENDO,
    };

    /**
     * @brief code object for EBuildTarget
     * 
     */
    struct CODE
    {
        inline static const char *BUILD_TARGET_UNDEFINED = "Undefined";
        inline static const char *BUILD_TARGET_LINUX = "Linux";
        inline static const char *BUILD_TARGET_WINDOWS = "Windows";
        inline static const char *BUILD_TARGET_MACOS = "MacOS";
        inline static const char *BUILD_TARGET_ANDROID = "Android";
        inline static const char *BUILD_TARGET_IOS = "IOS";
        inline static const char *BUILD_TARGET_WEB = "Web";
        inline static const char *BUILD_TARGET_PS = "PS";
        inline static const char *BUILD_TARGET_XBOX = "XBOX";
        inline static const char *BUILD_TARGET_NINTENDO = "Nintendo";
    };

    /**
     * @brief convert EBuildTarget enum to string
     * 
     * @param buildTargetEnum 
     * @return std::string 
     */
    static std::string toString(const ENUM &buildTargetEnum)
    {
        std::string result = CODE::BUILD_TARGET_UNDEFINED;

        switch (buildTargetEnum)
        {
            case ENUM::BUILD_TARGET_LINUX: { result = CODE::BUILD_TARGET_LINUX; } break;
            case ENUM::BUILD_TARGET_WINDOWS: { result = CODE::BUILD_TARGET_WINDOWS; } break;
            case ENUM::BUILD_TARGET_MACOS: { result = CODE::BUILD_TARGET_MACOS; } break;
            case ENUM::BUILD_TARGET_ANDROID: { result = CODE::BUILD_TARGET_ANDROID; } break;
            case ENUM::BUILD_TARGET_IOS: { result = CODE::BUILD_TARGET_IOS; } break;
            case ENUM::BUILD_TARGET_WEB: { result = CODE::BUILD_TARGET_WEB; } break;
            case ENUM::BUILD_TARGET_PS: { result = CODE::BUILD_TARGET_PS; } break;
            case ENUM::BUILD_TARGET_XBOX: { result = CODE::BUILD_TARGET_XBOX; } break;
            case ENUM::BUILD_TARGET_NINTENDO: { result = CODE::BUILD_TARGET_NINTENDO; } break;
            default: { result = CODE::BUILD_TARGET_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief convert EBuildTarget string to enum
     * 
     * @param buildTargetString 
     * @return ENUM 
     */
    static ENUM toEnum(const char *&buildTargetString)
    {
        ENUM result = ENUM::BUILD_TARGET_UNDEFINED;

        if (buildTargetString == CODE::BUILD_TARGET_LINUX)
        {
            result = ENUM::BUILD_TARGET_LINUX;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_WINDOWS)
        {
            result = ENUM::BUILD_TARGET_WINDOWS;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_MACOS)
        {
            result = ENUM::BUILD_TARGET_MACOS;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_ANDROID)
        {
            result = ENUM::BUILD_TARGET_ANDROID;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_IOS)
        {
            result = ENUM::BUILD_TARGET_IOS;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_WEB)
        {
            result = ENUM::BUILD_TARGET_WEB;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_PS)
        {
            result = ENUM::BUILD_TARGET_PS;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_XBOX)
        {
            result = ENUM::BUILD_TARGET_XBOX;
        }
        else if (buildTargetString == CODE::BUILD_TARGET_NINTENDO)
        {
            result = ENUM::BUILD_TARGET_NINTENDO;
        }
        else
        {
            result = ENUM::BUILD_TARGET_UNDEFINED;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_BUILD_ENUMS_HH
