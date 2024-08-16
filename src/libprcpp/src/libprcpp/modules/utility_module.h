#ifndef LIBPRCPP_UTILITY_MODULE_H
#define LIBPRCPP_UTILITY_MODULE_H
#include <libprcpp/base/config.h>
#include <libprcpp/base/export.h>

#include <libprcpp/enums/requirement_enums.h>
#include <libprcpp/enums/time_enums.h>

#include <string>
#include <random>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <ctime>
#include <chrono>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <array>

#if LIBPRCPP_PROJECT_USING_OPENSSL
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if PROJECT_BUILD_COMPILER_ID == 1
// RESERVED
#elif PROJECT_BUILD_COMPILER_ID == 2
#pragma warning (push)
#pragma warning (disable : 4996)
#pragma warning (disable : 4244)
#elif PROJECT_BUILD_COMPILER_ID == 3
// RESERVED
#endif

namespace libprcpp
{

/**
 * @brief utility module class
 * 
 */
class CUtilityModule
{
private:
    const std::string m_numeric = "0123456789";
    const std::string m_alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string m_alphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const std::string m_specialCharacter = "~!@#$%^&*()_+{}|:\"<>?`-=[]';,./\\";
    const std::string m_alphanumericWithSpecialCharacter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~!@#$%^&*-_=+";

public:
    CUtilityModule(/* args */);
    ~CUtilityModule();

    /**
     * @brief format string source, find match query and replace it
     * 
     * @param source 
     * @param query 
     * @param replacement 
     */
    void findAndReplaceAll(std::string &source, const std::string &query, const std::string &replacement);

    /**
     * @brief find each keywords from source
     * 
     * @note return value is how many keyword that've been found
     * 
     * @param source 
     * @param keywords 
     * @param foundKeywords 
     * @return int 
     */
    int  findEachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords);

    /**
     * @brief find keyword before "keywordBefore" param
     * 
     * @param source 
     * @param keywordBefore 
     * @param extraction 
     * @return true 
     * @return false 
     */
    bool findKeywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction);

    /**
     * @brief find keyword after "keywordAfter" param
     * 
     * @param source 
     * @param keywordAfter 
     * @param extraction 
     * @return true 
     * @return false 
     */
    bool findKeywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction);

    /**
     * @brief generate random number
     * 
     * @param min 
     * @param max 
     * @return int 
     */
    int generateRandomNumber(const int min, const int max);

    /**
     * @brief generate random number
     * 
     * @param min 
     * @param max 
     * @return long 
     */
    long generateRandomNumber(const long min, const long max);

    /**
     * @brief generate random number
     * 
     * @param min 
     * @param max 
     * @return long long 
     */
    long long generateRandomNumber(const long long min, const long long max);

    /**
     * @brief generate random number
     * 
     * @param min 
     * @param max 
     * @return float 
     */
    float generateRandomNumber(const float min, const float max);

    /**
     * @brief generate random number
     * 
     * @param min 
     * @param max 
     * @return double 
     */
    double generateRandomNumber(const double min, const double max);

    /**
     * @brief generate 16 random bytes in array
     * 
     * @return std::array<uint8_t, 16> 
     */
    std::array<uint8_t, 16> generateRandomBytes();

    /**
     * @brief generate random alphanumeric
     * 
     * @param length 
     * @return std::string 
     */
    std::string generateRandomAlphanumeric(int length);

    /**
     * @brief generate random alphanumeric with special character
     * 
     * @param length 
     * @return std::string 
     */
    std::string generateRandomAlphanumericWithSpecialCharacter(int length);

    /**
     * @brief change input letter case
     * 
     * @param input 
     * @param letterCase 0:lowercase, 1:uppercase, 2:mixcase
     * @return std::string 
     */
    std::string changeInputLetterCase(const std::string input, const int letterCase);

    /**
     * @brief generate uuid v1 ( MAC address & clock sequence ) for current system
     * 
     * @note please use try catch, since platform dependent may caught exception
     * 
     * @return std::string 
     */
    std::string generateUuidV1();

    /**
     * @brief generate uuid v4 for current system
     * 
     * @note please use try catch, since platform dependent may caught exception
     * 
     * @return std::string 
     */
    std::string generateUuidV4();

    /**
     * @brief check if input is alphabetic value
     * 
     * @param input 
     * @return true 
     * @return boolean
     */
    bool checkInputIsAlphabetic(const std::string input) const;

    /**
     * @brief check if input is alphanumeric value
     * 
     * @param input 
     * @return true 
     * @return boolean
     */
    bool checkInputIsAlphaNumeric(const std::string input) const;

    /**
     * @brief check if input password meet requirement param
     * 
     * @param input 
     * @param requirement 
     * @return true if meet requirement
     */
    bool checkInputPasswordMeetRequirement(const std::string &input, const ERequirementPasswordInput::Enum &requirement) const;

    /**
     * @brief check if input username meet requirement param
     * 
     * @param input 
     * @param requirement 
     * @return false if illegal
     */
    bool checkInputUsernameMeetRequirement(const std::string &input, const ERequirementUsernameInput::Enum &requirement) const;

#if LIBPRCPP_PROJECT_USING_OPENSSL
    /**
     * @brief base64 encoding
     * 
     * @param input 
     * @return std::string 
     */
    std::string base64encode(const std::string &input);

    /**
     * @brief base64 decoding
     * 
     * @param input 
     * @return std::string 
     */
    std::string base64decode(const std::string &input);
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

    // date and time structure
    struct SDateAndTime
    {
        // UTC data structure
        struct SUTC
        {
            // timezone utc structure
            struct STimeZone
            {
                // default: UTC +00:00
                std::string toString();

                // @param timeOffset from -11 to 14
                std::string toString(const int &timeOffset, const bool &ISO8601 = true);
            };
            // time zone utc data access
            STimeZone TimeZone = STimeZone();

            // utc year structure
            struct SUTCYear
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);
            };
            // utc year data access
            SUTCYear Year = SUTCYear();

            // utc month structure
            struct SUTCMonth
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);
            };
            // utc month data access
            SUTCMonth Month = SUTCMonth();

            // utc date structure
            struct SUTCDay
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);
            };
            // utc date data access
            SUTCDay Day = SUTCDay();

            // utc hour structure
            struct SUTCHour
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);
            };
            // utc hour data access
            SUTCHour Hour = SUTCHour();

            // utc minute structure
            struct SUTCMinute
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);
            };
            // utc minute data access
            SUTCMinute Minute = SUTCMinute();

            // utc second structure
            struct SUTCSecond
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);
            };
            // utc second data access
            SUTCSecond Second = SUTCSecond();

            // utc YYYYMMDD structure
            struct SUTCYearMonthDay
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);

                std::string toStringISO8601(const int &timeOffset = 0);
            };
            // utc YYYYMMDD data access
            SUTCYearMonthDay YYYYMMDD = SUTCYearMonthDay();

            // utc hhmmss structure
            struct SUTCHourMinuteSecond
            {
                int toInt(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);
            };
            // utc hhmmss data access
            SUTCHourMinuteSecond hhmmss = SUTCHourMinuteSecond();

            // utc YYYYMMDDhhmmss structure
            struct SUTCYearMonthDayHourMinuteSecond
            {
                long toInt64(const int &timeOffset = 0);

                std::string toString(const int &timeOffset = 0);

                std::string toStringSecondsOffset(const int &secondsOffset = 0);
            };
            // utc YYYYMMDDhhmmss data access
            SUTCYearMonthDayHourMinuteSecond YYYYMMDDhhmmss = SUTCYearMonthDayHourMinuteSecond();
        };
        // utc date and time data access
        SUTC UTC = SUTC();
    };
    // date and time data access
    SDateAndTime DateAndTime = SDateAndTime();
};

// namespace utilityFunctions for quick access common utilities
namespace utilityFunctions
{

/**
 * @brief format string source, find match query and replace it
 * 
 * @param source 
 * @param query 
 * @param replacement 
 */
void findAndReplaceAll(std::string &source, const std::string &query, const std::string &replacement);

/**
 * @brief find each keywords from source
 * 
 * @note return value is how many keyword that've been found
 * 
 * @param source 
 * @param keywords 
 * @param foundKeywords 
 * @return int 
 */
int  findEachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords);

/**
 * @brief find keyword before "keywordBefore" param
 * 
 * @param source 
 * @param keywordBefore 
 * @param extraction 
 * @return true 
 * @return false 
 */
bool findKeywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction);

/**
 * @brief find keyword after "keywordAfter" param
 * 
 * @param source 
 * @param keywordAfter 
 * @param extraction 
 * @return true 
 * @return false 
 */
bool findKeywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction);

/**
 * @brief generate random number
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int generateRandomNumber(const int min, const int max);

/**
 * @brief generate random number
 * 
 * @param min 
 * @param max 
 * @return long 
 */
long generateRandomNumber(const long min, const long max);

/**
 * @brief generate random number
 * 
 * @param min 
 * @param max 
 * @return long long 
 */
long long generateRandomNumber(const long long min, const long long max);

/**
 * @brief generate random number
 * 
 * @param min 
 * @param max 
 * @return float 
 */
float generateRandomNumber(const float min, const float max);

/**
 * @brief generate random number
 * 
 * @param min 
 * @param max 
 * @return double 
 */
double generateRandomNumber(const double min, const double max);

/**
 * @brief generate 16 random bytes in array
 * 
 * @return std::array<uint8_t, 16> 
 */
std::array<uint8_t, 16> generateRandomBytes();

/**
 * @brief generate random alphanumeric
 * 
 * @param length 
 * @return std::string 
 */
std::string generateRandomAlphanumeric(int length);

/**
 * @brief generate random alphanumeric with special character
 * 
 * @param length 
 * @return std::string 
 */
std::string generateRandomAlphanumericWithSpecialCharacter(int length);

/**
 * @brief change input letter case
 * 
 * @param input 
 * @param letterCase 0:lowercase, 1:uppercase, 2:mixcase
 * @return std::string 
 */
std::string changeInputLetterCase(const std::string input, const int letterCase);

/**
 * @brief generate uuid v1 ( MAC address & clock sequence ) for current system
 * 
 * @note please use try catch, since platform dependent may caught exception
 * 
 * @return std::string 
 */
std::string generateUuidV1();

/**
 * @brief generate uuid v4 for current system
 * 
 * @note please use try catch, since platform dependent may caught exception
 * 
 * @return std::string 
 */
std::string generateUuidV4();

/**
 * @brief check if input is alphabetic value
 * 
 * @param input 
 * @return true 
 * @return boolean
 */
bool checkInputIsAlphabetic(const std::string input);

/**
 * @brief check if input is alphanumeric value
 * 
 * @param input 
 * @return true 
 * @return boolean
 */
bool checkInputIsAlphaNumeric(const std::string input);

/**
 * @brief check if input password meet requirement param
 * 
 * @param input 
 * @param requirement 
 * @return true if meet requirement
 */
bool checkInputPasswordMeetRequirement(const std::string &input, const ERequirementPasswordInput::Enum &requirement);

/**
 * @brief check if input username meet requirement param
 * 
 * @param input 
 * @param requirement 
 * @return false if illegal
 */
bool checkInputUsernameMeetRequirement(const std::string &input, const ERequirementUsernameInput::Enum &requirement);

#if LIBPRCPP_PROJECT_USING_OPENSSL
/**
 * @brief base64 encoding
 * 
 * @param input 
 * @return std::string 
 */
std::string base64encode(const std::string &input);

/**
 * @brief base64 decoding
 * 
 * @param input 
 * @return std::string 
 */
std::string base64decode(const std::string &input);
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

namespace dateAndTime
{

namespace UTC
{

    namespace timeZone
    {
        // default: UTC +00:00
        std::string toString();

        // @param timeOffset from -11 to 14
        std::string toString(const int &timeOffset, const bool &ISO8601 = true);
    } // namespace timeZone

    namespace year
    {
        int toInt(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);
    } // namespace year

    namespace month
    {
        int toInt(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);
    } // namespace month

    namespace day
    {
        int toInt(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);
    } // namespace day

    namespace hour
    {
        int toInt(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);
    } // namespace hour

    namespace second
    {
        int toInt(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);
    } // namespace second

    namespace YYYYMMDD
    {
        int toInt(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);

        std::string toStringISO8601(const int &timeOffset = 0);
    } // namespace YYYYMMDD

    namespace hhmmss
    {
        int toInt(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);
    } // namespace hhmmss

    namespace YYYYMMDDhhmmss
    {
        long toInt64(const int &timeOffset = 0);

        std::string toString(const int &timeOffset = 0);

        std::string toStringSecondsOffset(const int &secondsOffset = 0);
    } // namespace YYYYMMDDhhmmss
    

} // namespace UTC

} // namespace dateAndTime

} // namespace utilityFunctions

} // namespace libprcpp

#endif // LIBPRCPP_UTILITY_MODULE_H
