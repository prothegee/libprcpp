#ifndef LIBPRCPP_DATE_AND_TIME_MODULE_HH
#define LIBPRCPP_DATE_AND_TIME_MODULE_HH
#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>

#include <libprcpp/enums/languages_enums.hh>

namespace libprcpp
{

/**
 * @brief date and time module class
 * 
 */
class CDateAndTime
{
private:
    /* data */

public:
    CDateAndTime(/* args */);
    ~CDateAndTime();

    /**
     * @brief UTC structure
     * 
     */
    struct SUTC
    {
        struct STimeZone
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
        };
        /**
         * @brief timezone object access
         * 
         */
        STimeZone TimeZone = STimeZone();

        /**
         * @brief year structure
         * 
         */
        struct SYear
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
        };
        /**
         * @brief year object access
         * 
         */
        SYear Year = SYear();

        /**
         * @brief month structure
         * 
         */
        struct SMonth
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
             * @param languageENUM default "en"
             * @param timeOffset 
             * @return std::string 
             */
            std::string toStringHuman(const ELanguage::ENUM &languageENUM, const int &timeOffset = 0);
        };
        /**
         * @brief month object access
         * 
         */
        SMonth Month = SMonth();

        /**
         * @brief day structure
         * 
         */
        struct SDay
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
        };
        /**
         * @brief day object access
         * 
         */
        SDay Day = SDay();

        /**
         * @brief hour structure
         * 
         */
        struct SHour
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
        };
        /**
         * @brief hour object access
         * 
         */
        SHour Hour = SHour();

        /**
         * @brief minute structure
         * 
         */
        struct SMinute
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
        };
        /**
         * @brief minute object access
         * 
         */
        SMinute Minute = SMinute();

        /**
         * @brief second structure
         * 
         */
        struct SSecond
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
        };
        /**
         * @brief second object access
         * 
         */
        SSecond Second = SSecond();

        /**
         * @brief YYYYMMDD structure
         * 
         */
        struct SYYYYMMDD
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
        };
        /**
         * @brief YYYYMMDD object access
         * 
         */
        SYYYYMMDD YYYYMMDD = SYYYYMMDD();

        /**
         * @brief hhmmss structure
         * 
         */
        struct SHhMmSs
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
        };
        /**
         * @brief hhmmss object access
         * 
         */
        SHhMmSs hhmmss = SHhMmSs();

        /**
         * @brief YYYYMMDDhhmmss structure
         * 
         */
        struct SYYYYMMDDhhmmss
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
        };
        /**
         * @brief YYYYMMDDhhmmss object access
         * 
         */
        SYYYYMMDDhhmmss YYYYMMDDhhmmss = SYYYYMMDDhhmmss();

        /**
         * @brief YYYYMMDDhhmmssms structure with millisecond
         * 
         */
        struct SYYYYMMDDhhmmssms
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
        };
        /**
         * @brief YYYYMMDDhhmmssms (millisecond) object access
         * 
         */
        SYYYYMMDDhhmmssms YYYYMMDDhhmmssms = SYYYYMMDDhhmmssms();

        /**
         * @brief YYYYMMDDhhmmssms structure with microsecond
         * 
         */
        struct SYYYYMMDDhhmmssmc
        {
            /* data */
        }; 
        /**
         * @brief YYYYMMDDhhmmssmc (microsecond) object access
         * 
         */
        SYYYYMMDDhhmmssmc YYYYMMDDhhmmssmc = SYYYYMMDDhhmmssmc();

        /**
         * @brief YYYYMMDDhhmmssms structure with nanosecond
         * 
         */
        struct SYYYYMMDDhhmmssnn
        {
            /* data */
        };
        /**
         * @brief YYYYMMDDhhmmssnn (nanosecond) object access
         * 
         */
        SYYYYMMDDhhmmssnn YYYYMMDDhhmmssnn = SYYYYMMDDhhmmssnn();
    };
    /**
     * @brief UTC object access
     * 
     */
    SUTC UTC = SUTC();
};

namespace dateAndTimeFunctions
{
    namespace UTC
    {
        namespace timezone
        {
            /**
             * @brief get current time string with default timezone +0 or 0
             * 
             * @return std::string 
             */
            std::string toString();

            /**
             * @brief get current time string with time offset option with ISO8601
             * 
             * @param timeOffset default 0
             * @param ISO8601 default true
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
             * @param languageENUM default "en"
             * @param timeOffset 
             * @return std::string 
             */
            std::string toStringHuman(const ELanguage::ENUM &languageENUM, const int &timeOffset = 0);
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
             * @param YYYYMMDDhhmmss e.g. 2020-10-05T23:59:59
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
             * @param YYYYMMDDhhmmssms e.g. 2020-10-05T23:59:59
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
    } // namespace UTC
} // namespace dateAndTimeFunctions

} // namespace libprcpp

#endif // LIBPRCPP_DATE_AND_TIME_MODULE_HH
