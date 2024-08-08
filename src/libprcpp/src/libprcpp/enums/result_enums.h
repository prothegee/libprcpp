#ifndef LIBPRCPP_RESULT_ENUMS_H
#define LIBPRCPP_RESULT_ENUMS_H
#include <libprcpp/types/basic_types.h>

namespace libprcpp
{

/**
 * @brief result enum structure
 * 
 */
struct EResult
{
    enum Enum : TInt32
    {
        RESULT_EXISTS_NOT = -2,
        RESULT_ERROR = -1,
        RESULT_UNDEFINED = 0,
        RESULT_OK = 1,
        RESULT_EXISTS = 2,
    };
};

} // namespace libprcpp

#endif // LIBPRCPP_RESULT_ENUMS_H
