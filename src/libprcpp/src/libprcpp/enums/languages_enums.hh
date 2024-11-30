#ifndef LIBPRCPP_LANGAUGE_ENUMS_HH
#define LIBPRCPP_LANGAUGE_ENUMS_HH
#include <cstdint>

namespace libprcpp
{

// IMPORTANT: check multiple languages

/**
 * @brief language enum structure
 * 
 */
struct ELanguage
{
    /**
     * @brief enum object for ELanguage
     * 
     */
    enum Enum : int32_t
    {
        LANGUAGE_UNDEFINED = 0,
        LANGUAGE_ENGLISH,
        LANGUAGE_BAHASA,
    };

    /**
     * @brief code object for ELanguage
     * 
     */
    struct Code
    {
        inline static const char *LANGUAGE_UNDEFINED = "undefined";
        inline static const char *LANGUAGE_ENGLISH = "en";
        inline static const char *LANGUAGE_BAHASA = "id";
    };

    /**
     * @brief convert ELanguage enum to string
     * 
     * @param languageEnum 
     * @return const char* 
     */
    static const char *toString(const Enum &languageEnum)
    {
        const char *result = Code::LANGUAGE_UNDEFINED;

        switch (languageEnum)
        {
            case Enum::LANGUAGE_ENGLISH: { result = Code::LANGUAGE_ENGLISH; } break;
            case Enum::LANGUAGE_BAHASA: { result = Code::LANGUAGE_BAHASA; } break;
            default: { result = Code::LANGUAGE_ENGLISH; } break;
        }

        return result;
    }

    /**
     * @brief convert ELanguage string to enum
     * 
     * @param languageString 
     * @return Enum 
     */
    static Enum toEnum(const char *languageString)
    {
        Enum result = Enum::LANGUAGE_UNDEFINED;

        if (languageString == Code::LANGUAGE_ENGLISH)
        {
            result = Enum::LANGUAGE_ENGLISH;
        }
        else if (languageString == Code::LANGUAGE_BAHASA)
        {
            result = Enum::LANGUAGE_BAHASA;
        }
        else
        {
            result = Enum::LANGUAGE_ENGLISH;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_LANGAUGE_ENUMS_HH
