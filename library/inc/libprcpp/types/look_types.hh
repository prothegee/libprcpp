#ifndef LIBPRCPP_LOOK_TYPES_HH
#define LIBPRCPP_LOOK_TYPES_HH
#include <string>

namespace libprcpp
{

/**
 * @brief type for "to look & to replace"
 */
struct TLookAndReplace
{
    std::string to_look;
    std::string to_replace;
};

} // namespace libprcpp

#endif // LIBPRCPP_LOOK_TYPES_HH
