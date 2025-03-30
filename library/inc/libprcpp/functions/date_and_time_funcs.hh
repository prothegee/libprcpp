#ifndef LIBPRCPP_DATE_AND_TIMES_FUNCS_HH
#define LIBPRCPP_DATE_AND_TIMES_FUNCS_HH
#include <libprcpp/config.hh>
#include <libprcpp/export.hh>

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>

namespace libprcpp
{
namespace dateAndTimeFunctions
{


/**
 * @brief get this local machine timzone
 * 
 * @return int 
 */
int localTimeZone();


// UTC timezone
// timeOffset has limit for Earth time
namespace UTC
{
    namespace timeZone
    {
        /**
         * @brief get current time string with default timezone of 0
         * 
         * @return std::string 
         */
        std::string toString();

        /**
         * @brief get current time string with time offset option with ISO8601
         * 
         * @param timeOffset default 0
         * @param ISO8601 default true, if true YYYY-MM-DDThh:mm:ss otherwise YYYY-MM-DD hh:mm:ss
         * @return std::string 
         */
        std::string toStringOffset(const int &timeOffset = 0, const bool &ISO8601 = true);
    } // namespace timeZone


    namespace year
    {
        /**
         * @brief get current year as int
         * 
         * @param timeOffset default 0
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get current year as string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);
    } // namespace year


    namespace month
    {
        /**
         * @brief get current month as int
         * 
         * @param timeOffset default 0
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get current month as string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);

        /**
         * @brief get current month as human string, e.g. Jan, Jun, Jul, etc.
         * 
         * @param language 1:en (English) 2:id (Bahasa)
         * @param timeOffset 
         * @return std::string 
         */
        std::string toStringHuman(const int &language = 1, const int &timeOffset = 0);
    } // namespace month


    namespace day
    {
        /**
         * @brief get current day as int
         * 
         * @param timeOffset default 0
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get current day as string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);
    } // namespace day


    namespace hour
    {
        /**
         * @brief get current hour as int
         * 
         * @param timeOffset default 0
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get current hour as string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);
    } // namespace hour


    namespace minute
    {
        /**
         * @brief get current minute as int
         * 
         * @param timeOffset default 0
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get current minute as string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);
    } // namespace minute


    namespace second
    {
        /**
         * @brief get current second as int
         * 
         * @param timeOffset default 0
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get current second as string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);
    } // namespace second


    namespace YYYYMMDD
    {
        /**
         * @brief get year, month, & day as YYYYMMDD int
         * 
         * @param timeOffset 
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get year, month, & day as YYYYMMDD string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);

        /**
         * @brief get Year, Month, & Day as YYYY-MM-DD string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toStringISO8601(const int &timeOffset = 0);
    } // namespace YYYYMMDD


    namespace hhmmss
    {
        /**
         * @brief get hour, minute, & second as hhmmss int
         * 
         * @param timeOffset 
         * @return int 
         */
        int toInt(const int &timeOffset = 0);

        /**
         * @brief get hour, minute, & second as hhmmss string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);

        /**
         * @brief get hour, minute, & second as hh:mm:ss sting
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toStringHuman(const int &timeOffset = 0);
    } // namespace hhmmss


    namespace YYYYMMDDhhmmss
    {
        /**
         * @brief get YYYYMMDDhhmmss as int64
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toInt64(const int &timeOffset = 0);

        /**
         * @brief convert YYYYMMDDhhmmss to millis
         * 
         * @param YYYYMMDDhhmmss 
         * @return int64_t 
         */
        int64_t toMillis(const std::string &YYYYMMDDhhmmss);

        /**
         * @brief use current date and time as millis
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toMillisNow(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmss as is
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmss as YYYY-MM-DDThh:mm:ss or YYYY-MM-DD hh:mm:ss if useTimeSign = false
         * 
         * @param timeOffset 
         * @param useTimeSign 
         * @return std::string 
         */
        std::string toStringHuman(const int &timeOffset = 0, const bool &useTimeSign = true);

        /**
         * @brief get YYYYMMDDhhmmss without time offset limit
         * 
         * @param secondsOffset 
         * @return std::string 
         */
        std::string toStringSecondsOffset(const int &secondsOffset = 0);
    } // namespace YYYYMMDDhhmmss


    namespace YYYYMMDDhhmmssms
    {
        /**
         * @brief get YYYYMMDDhhmmssms as int64
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toInt64(const int &timeOffset = 0);

        /**
         * @brief convert YYYYMMDDhhmmssms to millis
         * 
         * @param YYYYMMDDhhmmssms 
         * @return int64_t 
         */
        int64_t toMillis(const std::string &YYYYMMDDhhmmssms);

        /**
         * @brief get YYYYMMDDhhmmssms as millis
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toMillisNow(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmssms as is string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmssms as YYYY-MM-DDThh:mm:ss.sss or YYYY-MM-DD hh:mm:ss.sss if useTimeSign = false
         * 
         * @param timeOffset 
         * @param useTimeSign 
         * @return std::string 
         */
        std::string toStringHuman(const int &timeOffset = 0, const bool &useTimeSign = true);

        /**
         * @brief get YYYYMMDDhhmmssms without time offset limit
         * 
         * @param secondsOffset 
         * @return std::string 
         */
        std::string toStringSecondOffset(const int &secondsOffset = 0);
    } // namespace YYYYMMDDhhmmssms


    namespace YYYYMMDDhhmmssµs
    {
        /**
         * @brief get YYYYMMDDhhmmssµs as int64
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toInt64(const int &timeOffset = 0);

        /**
         * @brief convert YYYYMMDDhhmmssµs to millis
         * 
         * @param YYYYMMDDhhmmssµs 
         * @return int64_t 
         */
        int64_t toMillis(const std::string &YYYYMMDDhhmmssµs);

        /**
         * @brief get YYYYMMDDhhmmssµs as millis
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toMillisNow(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmssµs as is string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmssµs as YYYY-MM-DDThh:mm:ss.ssssss or YYYY-MM-DD hh:mm:ss.ssssss if useTimeSign = false
         * 
         * @param timeOffset 
         * @param useTimeSign 
         * @return std::string 
         */
        std::string toStringHuman(const int &timeOffset = 0, const bool &useTimeSign = true);

        /**
         * @brief get YYYYMMDDhhmmssµs without time offset limit
         * 
         * @param secondsOffset 
         * @return std::string 
         */
        std::string toStringSecondOffset(const int &secondsOffset = 0);
    } // namespace YYYYMMDDhhmmssµs


    namespace YYYYMMDDhhmmssns
    {
        /**
         * @brief get YYYYMMDDhhmmssns as int64
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toInt64(const int &timeOffset = 0);

        /**
         * @brief convert YYYYMMDDhhmmssns to millis
         * 
         * @param YYYYMMDDhhmmssns 
         * @return int64_t 
         */
        int64_t toMillis(const std::string &YYYYMMDDhhmmssns);

        /**
         * @brief get YYYYMMDDhhmmssns as millis
         * 
         * @param timeOffset 
         * @return int64_t 
         */
        int64_t toMillisNow(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmssns as is string
         * 
         * @param timeOffset 
         * @return std::string 
         */
        std::string toString(const int &timeOffset = 0);

        /**
         * @brief get YYYYMMDDhhmmssns as YYYY-MM-DDThh:mm:ss.sssssssss or YYYY-MM-DD hh:mm:ss.sssssssss if useTimeSign = false
         * 
         * @param timeOffset 
         * @param useTimeSign 
         * @return std::string 
         */
        std::string toStringHuman(const int &timeOffset = 0, const bool &useTimeSign = true);

        /**
         * @brief get YYYYMMDDhhmmssns without time offset limit
         * 
         * @param secondsOffset 
         * @return std::string 
         */
        std::string toStringSecondOffset(const int &secondsOffset = 0);
    } // namespace YYYYMMDDhhmmssns
} // namespace UTC


} // namespace dateAndTimeFunctions
} // namespace libprcpp

#endif // LIBPRCPP_DATE_AND_TIMES_FUNCS_HH
