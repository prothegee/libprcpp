#ifndef PRGENT_RETURN_ENUMS_HH
#define PRGENT_RETURN_ENUMS_HH
#include <libprcpp/types/basic_types.hh>

using namespace libprcpp;

namespace prgent
{

/**
 * @brief prgent return main result enum
 */
enum EReturnMainResult : i32
{
    RETURN_MAIN_RESULT_OK,
    RETURN_MAIN_RESULT_SHOW_HELP,
    RETURN_MAIN_RESULT_GENERATE_MODE_IS_UNDEFINED,
    RETURN_MAIN_RESULT_GENERATE_MODE_NOT_SUPPORTED,
    RETURN_MAIN_RESULT_ERROR_INPUT_IS_REQUIRED,
    RETURN_MAIN_RESULT_ERROR_ENCODE_IMAGE,
    RETURN_MAIN_RESULT_ERROR_DEFAULT, // last option/position
};

} // namespace prgent

#endif // PRGENT_RETURN_ENUMS_HH
