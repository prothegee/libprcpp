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
    enum ENUM : int32_t
    {
        LANGUAGE_UNDEFINED = 0,
        LANGUAGE_ENGLISH,
        LANGUAGE_BAHASA,
    };

    /**
     * @brief code object for ELanguage
     * 
     */
    struct CODE
    {
        inline static const char *LANGUAGE_UNDEFINED = "undefined";
        inline static const char *LANGUAGE_ENGLISH = "en";
        inline static const char *LANGUAGE_BAHASA = "id";
    };

    /**
     * @brief convert ELanguage enum to string
     * 
     * @param languageENUM 
     * @return const char* 
     */
    static const char *toString(const ENUM &languageENUM)
    {
        const char *result = CODE::LANGUAGE_UNDEFINED;

        switch (languageENUM)
        {
            case ENUM::LANGUAGE_ENGLISH: { result = CODE::LANGUAGE_ENGLISH; } break;
            case ENUM::LANGUAGE_BAHASA: { result = CODE::LANGUAGE_BAHASA; } break;
            default: { result = CODE::LANGUAGE_ENGLISH; } break;
        }

        return result;
    }

    /**
     * @brief convert ELanguage string to enum
     * 
     * @param languageString 
     * @return ENUM 
     */
    static ENUM toENUM(const char *languageString)
    {
        ENUM result = ENUM::LANGUAGE_UNDEFINED;

        if (languageString == CODE::LANGUAGE_ENGLISH)
        {
            result = ENUM::LANGUAGE_ENGLISH;
        }
        else if (languageString == CODE::LANGUAGE_BAHASA)
        {
            result = ENUM::LANGUAGE_BAHASA;
        }
        else
        {
            result = ENUM::LANGUAGE_ENGLISH;
        }

        return result;
    }
};

} // namespace libprcpp

#endif // LIBPRCPP_LANGAUGE_ENUMS_HH
