#ifndef LIBPRCPP_UTILITY_MODULE_HH
#define LIBPRCPP_UTILITY_MODULE_HH
#include <libprcpp/base/config.hh>
#include <libprcpp/base/export.hh>

#include <libprcpp/constants/string_const.hh>
#include <libprcpp/enums/requirement_enums.hh>
#include <libprcpp/enums/time_enums.hh>

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

#if LIBPRCPP_PROJECT_USING_JSONCPP
#include <json/json.h>
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

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
    /* data */

public:
    CUtilityModule(/* args */);
    ~CUtilityModule();

#if LIBPRCPP_PROJECT_USING_OPENSSL
    /**
     * @brief base 64 encoding
     * 
     * @note using openssl
     * 
     * @param input 
     * @return std::string 
     */
    std::string base64encode(const std::string &input);

    /**
     * @brief base 64 decoding
     * 
     * @note using openssl
     * 
     * @param input 
     * @return std::string 
     */
    std::string base64decode(const std::string &input);
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

    /**
     * @brief find structure
     * 
     */
    struct SFind
    {
        /**
         * @brief format string source, find match query and replace it
         * 
         * @param source 
         * @param query 
         * @param replacement 
         */
        void andReplaceAll(std::string &source, const std::string &query, const std::string &replacement);

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
        int eachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords);

        /**
         * @brief find keyword before "keywordBefore" param
         * 
         * @param source 
         * @param keywordBefore 
         * @param extraction 
         * @return true 
         * @return false 
         */
        bool keywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction);

        /**
         * @brief find keyword after "keywordAfter" param
         * 
         * @param source 
         * @param keywordAfter 
         * @param extraction 
         * @return true 
         * @return false 
         */
        bool keywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction);
    };
    /**
     * @brief find object access
     * 
     */
    SFind Find = SFind();

    /**
     * @brief generate structure
     * 
     */
    struct SGenerate
    {
        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return int 
         */
        int randomNumber(const int min, const int max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return long 
         */
        long randomNumber(const long min, const long max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return long long 
         */
        long long randomNumber(const long long min, const long long max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return float 
         */
        float randomNumber(const float min, const float max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return double 
         */
        double randomNumber(const double min, const double max);

        /**
         * @brief generate 16 random bytes in array
         * 
         * @return std::array<uint8_t, 16> 
         */
        std::array<uint8_t, 16> randomBytes();

        /**
         * @brief generate uuid v1 ( MAC address & clock sequence ) for current system
         * 
         * @note please use try catch, since platform dependent may caught exception
         * 
         * @return std::string 
         */
        std::string uuidV1();

        /**
         * @brief generate uuid v4 for current system
         * 
         * @note please use try catch, since platform dependent may caught exception
         * 
         * @return std::string 
         */
        std::string uuidV4();

        /**
         * @brief generate random alphanumeric
         * 
         * @param length 
         * @return std::string 
         */
        std::string randomAlphanumeric(int length);

        /**
         * @brief generate random alphanumeric with special character
         * 
         * @param length 
         * @return std::string 
         */
        std::string randomAlphanumericWithSpecialCharacter(int length);
    };
    /**
     * @brief generate object access
     * 
     */
    SGenerate Generate = SGenerate();

    /**
     * @brief change structure
     * 
     */
    struct SChange
    {
        /**
         * @brief change input letter case
         * 
         * @param input 
         * @param letterCase 0:lowercase, 1:uppercase, 2:mixcase
         * @return std::string 
         */
        std::string inputLetterCase(const std::string input, const int letterCase);
    };
    /**
     * @brief change object access
     * 
     */
    SChange Change = SChange();

#if LIBPRCPP_PROJECT_USING_JSONCPP
    /**
     * @brief json structure
     * 
     */
    struct SJson
    {
        /**
         * @brief get json from .json file
         * 
         * @param filePath 
         * @return Json::Value 
         */
        Json::Value fromFile(const std::string &filePath);

        /**
         * @brief get json value from jsonStringInput
         * 
         * @param jsonStringInput 
         * @param indent default 4
         * @param precision  default 16
         * @return Json::Value 
         */
        Json::Value fromString(const std::string &jsonStringInput, const int &indent = 4, const int &precision = 16);
    };
    /**
     * @brief json object access
     * 
     */
    SJson JSON = SJson();
#endif // LIBPRCPP_PROJECT_USING_JSONCPP
};

namespace utilityFunctions
{
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

    namespace find
    {
        /**
         * @brief format string source, find match query and replace it
         * 
         * @param source 
         * @param query 
         * @param replacement 
         */
        void andReplaceAll(std::string &source, const std::string &query, const std::string &replacement);

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
        int eachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords);

        /**
         * @brief find keyword before "keywordBefore" param
         * 
         * @param source 
         * @param keywordBefore 
         * @param extraction 
         * @return true 
         * @return false 
         */
        bool keywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction);

        /**
         * @brief find keyword after "keywordAfter" param
         * 
         * @param source 
         * @param keywordAfter 
         * @param extraction 
         * @return true 
         * @return false 
         */
        bool keywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction);
    } // namespace find

    namespace generate
    {
        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return int 
         */
        int randomNumber(const int min, const int max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return long 
         */
        long randomNumber(const long min, const long max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return long long 
         */
        long long randomNumber(const long long min, const long long max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return float 
         */
        float randomNumber(const float min, const float max);

        /**
         * @brief generate random number
         * 
         * @param min 
         * @param max 
         * @return double 
         */
        double randomNumber(const double min, const double max);

        /**
         * @brief generate 16 random bytes in array
         * 
         * @return std::array<uint8_t, 16> 
         */
        std::array<uint8_t, 16> randomBytes();

        /**
         * @brief generate uuid v1 ( MAC address & clock sequence ) for current system
         * 
         * @note please use try catch, since platform dependent may caught exception
         * 
         * @return std::string 
         */
        std::string uuidV1();

        /**
         * @brief generate uuid v4 for current system
         * 
         * @note please use try catch, since platform dependent may caught exception
         * 
         * @return std::string 
         */
        std::string uuidV4();

        /**
         * @brief generate random alphanumeric
         * 
         * @param length 
         * @return std::string 
         */
        std::string randomAlphanumeric(int length);

        /**
         * @brief generate random alphanumeric with special character
         * 
         * @param length 
         * @return std::string 
         */
        std::string randomAlphanumericWithSpecialCharacter(int length);
    } // namespace generate

    namespace change
    {
        /**
         * @brief change input letter case
         * 
         * @param input 
         * @param letterCase 0:lowercase, 1:uppercase, 2:mixcase
         * @return std::string 
         */
        std::string inputLetterCase(const std::string input, const int letterCase);
    } // namespace change

    namespace json
    {
        /**
         * @brief get json from .json file
         * 
         * @param filePath 
         * @return Json::Value 
         */
        Json::Value fromFile(const std::string &filePath);

        /**
         * @brief get json value from jsonStringInput
         * 
         * @param jsonStringInput 
         * @param indent default 4
         * @param precision  default 16
         * @return Json::Value 
         */
        Json::Value fromString(const std::string &jsonStringInput, const int &indent = 4, const int &precision = 16);
    } // namespace json
} // namespace utilityFunctions

} // namespace libprcpp

#if PROJECT_BUILD_COMPILER_ID == 1
// RESERVED
#elif PROJECT_BUILD_COMPILER_ID == 2
#pragma warning (pop)
#elif PROJECT_BUILD_COMPILER_ID == 3
// RESERVED
#endif

#endif // LIBPRCPP_UTILITY_MODULE_HH
