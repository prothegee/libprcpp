#ifndef LIBPRCPP_TIME_ENUMS_H
#define LIBPRCPP_TIME_ENUMS_H
#include <libprcpp/types/basic_types.h>

namespace libprcpp
{

/**
 * @brief enum time zone structure
 * 
 */
struct ETimeZoneUTC
{
    /**
     * @brief enum for ETimeZoneUTC
     * 
     */
    enum Enum : TInt32
    {
        TIME_ZONE_UTC_MINUS_11 = -11,
        TIME_ZONE_UTC_MINUS_10 = -10,
        TIME_ZONE_UTC_MINUS_09 = -9,
        TIME_ZONE_UTC_MINUS_08 = -8,
        TIME_ZONE_UTC_MINUS_07 = -7,
        TIME_ZONE_UTC_MINUS_06 = -6,
        TIME_ZONE_UTC_MINUS_05 = -5,
        TIME_ZONE_UTC_MINUS_04 = -4,
        TIME_ZONE_UTC_MINUS_03 = -3,
        TIME_ZONE_UTC_MINUS_02 = -2,
        TIME_ZONE_UTC_MINUS_01 = -1,
        TIME_ZONE_UTC_ZERO     =  0, // default
        TIME_ZONE_UTC_PLUS_01  =  1,
        TIME_ZONE_UTC_PLUS_02  =  2,
        TIME_ZONE_UTC_PLUS_03  =  3,
        TIME_ZONE_UTC_PLUS_04  =  4,
        TIME_ZONE_UTC_PLUS_05  =  5,
        TIME_ZONE_UTC_PLUS_06  =  6,
        TIME_ZONE_UTC_PLUS_07  =  7,
        TIME_ZONE_UTC_PLUS_08  =  8,
        TIME_ZONE_UTC_PLUS_09  =  9,
        TIME_ZONE_UTC_PLUS_10  =  10,
        TIME_ZONE_UTC_PLUS_11  =  11,
        TIME_ZONE_UTC_PLUS_12  =  12,
        TIME_ZONE_UTC_PLUS_13  =  13,
        TIME_ZONE_UTC_PLUS_14  =  14,
    };
};

} // namespace libprcpp

#endif // LIBPRCPP_TIME_ENUMS_H
