#ifndef LIBPRCPP_REQUIREMENT_ENUMS_HH
#define LIBPRCPP_REQUIREMENT_ENUMS_HH
#include <libprcpp/types/basic_types.hh>

namespace libprcpp
{

/**
 * @brief enum requirement password input structure
 * 
 */
struct ERequirementPasswordInput
{
    /**
     * @brief enum object for ERequirementPasswordInput
     * 
     */
    enum ENUM : TInt32
    {
        REQUIREMENT_PASSWORD_INPUT_UNDEFINED = 0,
        REQUIREMENT_PASSWORD_INPUT_MIN_LENGTH_6,
        REQUIREMENT_PASSWORD_INPUT_MIN_LENGTH_6_WITH_1_NUMERIC_AND_1_SPECIAL_CHARACTER,
    };
};

/**
 * @brief enum requirement username input
 * 
 */
struct ERequirementUsernameInput
{
    /**
     * @brief enum object for ERequirementUsernameInput
     * 
     */
    enum ENUM: TInt32
    {
        REQUIREMENT_USERNAME_INPUT_UNDEFINED = 0,
        REQUIREMENT_USERNAME_INPUT_ALPHANUMERIC_UNDERSCORE,
    };
};

} // namespace libprcpp

#endif // LIBPRCPP_REQUIREMENT_ENUMS_HH
