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
    enum Enum
    {
        BUILD_TARGET_UNDEFINED = 0,
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
    struct Code
    {
        inline static const std::string BUILD_TARGET_UNDEFINED = "Undefined";
        inline static const std::string BUILD_TARGET_LINUX = "Linux";
        inline static const std::string BUILD_TARGET_WINDOWS = "Windows";
        inline static const std::string BUILD_TARGET_MACOS = "MacOS";
        inline static const std::string BUILD_TARGET_ANDROID = "Android";
        inline static const std::string BUILD_TARGET_IOS = "IOS";
        inline static const std::string BUILD_TARGET_WEB = "Web";
        inline static const std::string BUILD_TARGET_PS = "PS";
        inline static const std::string BUILD_TARGET_XBOX = "XBOX";
        inline static const std::string BUILD_TARGET_NINTENDO = "Nintendo";
    };

    /**
     * @brief convert EBuildTarget enum to string
     * 
     * @param buildTargetEnum 
     * @return std::string 
     */
    static std::string toString(const Enum &buildTargetEnum)
    {
        std::string result = Code::BUILD_TARGET_UNDEFINED;

        switch (buildTargetEnum)
        {
            case Enum::BUILD_TARGET_LINUX: { result = Code::BUILD_TARGET_LINUX; } break;
            case Enum::BUILD_TARGET_WINDOWS: { result = Code::BUILD_TARGET_WINDOWS; } break;
            case Enum::BUILD_TARGET_MACOS: { result = Code::BUILD_TARGET_MACOS; } break;
            case Enum::BUILD_TARGET_ANDROID: { result = Code::BUILD_TARGET_ANDROID; } break;
            case Enum::BUILD_TARGET_IOS: { result = Code::BUILD_TARGET_IOS; } break;
            case Enum::BUILD_TARGET_WEB: { result = Code::BUILD_TARGET_WEB; } break;
            case Enum::BUILD_TARGET_PS: { result = Code::BUILD_TARGET_PS; } break;
            case Enum::BUILD_TARGET_XBOX: { result = Code::BUILD_TARGET_XBOX; } break;
            case Enum::BUILD_TARGET_NINTENDO: { result = Code::BUILD_TARGET_NINTENDO; } break;
            default: { result = Code::BUILD_TARGET_UNDEFINED; } break;
        }

        return result;
    }

    /**
     * @brief convert EBuildTarget string to enum
     * 
     * @param buildTargetString 
     * @return Enum 
     */
    static Enum toEnum(const std::string &buildTargetString)
    {
        Enum result = Enum::BUILD_TARGET_UNDEFINED;

        if (buildTargetString == Code::BUILD_TARGET_LINUX)
        {
            result = Enum::BUILD_TARGET_LINUX;
        }
        else if (buildTargetString == Code::BUILD_TARGET_WINDOWS)
        {
            result = Enum::BUILD_TARGET_WINDOWS;
        }
        else if (buildTargetString == Code::BUILD_TARGET_MACOS)
        {
            result = Enum::BUILD_TARGET_MACOS;
        }
        else if (buildTargetString == Code::BUILD_TARGET_ANDROID)
        {
            result = Enum::BUILD_TARGET_ANDROID;
        }
        else if (buildTargetString == Code::BUILD_TARGET_IOS)
        {
            result = Enum::BUILD_TARGET_IOS;
        }
        else if (buildTargetString == Code::BUILD_TARGET_WEB)
        {
            result = Enum::BUILD_TARGET_WEB;
        }
        else if (buildTargetString == Code::BUILD_TARGET_PS)
        {
            result = Enum::BUILD_TARGET_PS;
        }
        else if (buildTargetString == Code::BUILD_TARGET_XBOX)
        {
            result = Enum::BUILD_TARGET_XBOX;
        }
        else if (buildTargetString == Code::BUILD_TARGET_NINTENDO)
        {
            result = Enum::BUILD_TARGET_NINTENDO;
        }
        else
        {
            result = Enum::BUILD_TARGET_UNDEFINED;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_BUILD_ENUMS_HH
