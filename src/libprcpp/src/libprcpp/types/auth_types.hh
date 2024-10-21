#ifndef LIBPRCPP_AUTH_TYPES_HH
#define LIBPRCPP_AUTH_TYPES_HH

namespace libprcpp
{

/**
 * @brief type auth basic structure
 * 
 */
struct TAuthBasic
{
    const char *username;
    const char *password;
};

} // namespace libprcpp

#endif // LIBPRCPP_AUTH_TYPES_HH
