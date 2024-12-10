#ifndef LIBPRCPP_RESULT_ENUMS_HH
#define LIBPRCPP_RESULT_ENUMS_HH
#include <libprcpp/types/basic_types.hh>

namespace libprcpp
{

/**
 * @brief result enum structure
 * 
 */
struct EResult
{
    enum ENUM : TInt32
    {
        RESULT_UNDEFINED,
        RESULT_OK,
        RESULT_ERROR,
        RESULT_EXISTS,
        RESULT_DOESNT_EXISTS,
    };
};

} // namespace libprcpp

#endif // LIBPRCPP_RESULT_ENUMS_HH
