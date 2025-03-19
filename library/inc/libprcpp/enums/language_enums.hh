#ifndef LIBPRCPP_LANGUAGE_ENUMS_HH
#define LIBPRCPP_LANGUAGE_ENUMS_HH
#include <libprcpp/types/base_types.hh>

namespace libprcpp
{

/**
 * @brief language enum
 */
enum ELanguage : TI32
{
    LANGUAGE_UNDEFINED,     // undefined
    LANGUAGE_ENGLISH,       // en
    LANGUAGE_BAHASA,        // id
};

inline static const TChr *LANGUAGE_UNDEFINED_HINT = "undefined";
inline static const TChr *LANGUAGE_ENGLISH_HINT   = "en";
inline static const TChr *LANGUAGE_BAHASA_HINT    = "id";

/**
 * @brief get string value of related languageEnum param
 * 
 * @param languageEnum 
 * @return const TChr* 
 */
inline static const TChr *ELanguageToString(const ELanguage &languageEnum)
{
    switch (languageEnum)
    {
        case LANGUAGE_ENGLISH:  { return LANGUAGE_ENGLISH_HINT; } break;
        case LANGUAGE_BAHASA:   { return LANGUAGE_BAHASA_HINT; } break;
        default:                { return LANGUAGE_UNDEFINED_HINT; } break;
    }
}

/**
 * @brief get enum value of related languageString
 * 
 * @param languageString 
 * @return ELanguage 
 */
inline static ELanguage ELanguageToEnum(const TChr *languageString)
{
    if (languageString == LANGUAGE_ENGLISH_HINT)    { return LANGUAGE_ENGLISH; }
    if (languageString == LANGUAGE_BAHASA_HINT)     { return LANGUAGE_BAHASA; }
    return LANGUAGE_UNDEFINED;
}

} // namespace libprcpp

#endif // LIBPRCPP_LANGUAGE_ENUMS_HH
