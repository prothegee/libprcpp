#ifndef LIBPRCPP_STRING_CONST_HH
#define LIBPRCPP_STRING_CONST_HH
#include <string>

namespace libprcpp
{

/**
 * @brief string internal object access collection
 * 
 */
struct STRINGS_INTERNAL
{
    inline static const std::string numeric = "0123456789";
    inline static const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    inline static const std::string alphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    inline static const std::string special_character = "~!@#$%^&*()_+{}|:\"<>?`-=[]';,./\\";
    inline static const std::string alphanumeric_with_special_character = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~!@#$%^&*-_=+";

    inline static const std::string BASE36_DIGITS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    inline static const char HEX_DIGITS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
};

} // namespace libprcpp

#endif // LIBPRCPP_STRING_CONST_HH