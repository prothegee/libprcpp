#ifndef LIBPRCPP_UTILITY_FUNCS_HH
#define LIBPRCPP_UTILITY_FUNCS_HH
#include <libprcpp/config.hh>
#include <libprcpp/export.hh>
#include <libprcpp/constants/strings_const.hh>
#include <libprcpp/enums/result_enums.hh>
#include <libprcpp/types/base_types.hh>

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
#include <thread>
#include <memory>
#include <future>
#include <fstream>

#if LIBPRCPP_USING_OPENSSL
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#endif // LIBPRCPP_USING_OPENSSL

#if LIBPRCPP_USING_JSONCPP
#include <json/json.h>
#endif // LIBPRCPP_USING_JSONCPP

namespace libprcpp
{
namespace utilityFunctions
{

/**
 * @brief check if string param is numeric
 * 
 * @return true 
 * @return false 
 */
bool isNumeric(const std::string &input);

#if LIBPRCPP_USING_OPENSSL
/**
 * @brief encode base64
 * 
 * @note this function using openssl lib
 * 
 * @param input 
 * @return std::string 
 */
std::string base64encode(const std::string &input);

/**
 * @brief decode base64
 * 
 * @note this function using openssl lib
 * 
 * @param input 
 * @return 
 */
std::string base64decode(const std::string &input);
#endif // LIBPRCPP_USING_OPENSSL


namespace arg
{
    inline static const TChar *NOTHING_HERE = "nothing here";
} // namespace arg


namespace find
{
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
     * @brief format string source, find match query and replace it
     * 
     * @param source 
     * @param query 
     * @param replacement 
     * @return true 
     * @return false 
     */
    bool andReplaceAll(std::string &source, const std::string &query, const std::string &replacement);

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
     * @brief find input end with checkWith param
     * 
     * @param input 
     * @param checkWith 
     * @return true 
     * @return false 
     */
    bool inputEndsWith(const std::string &input, const std::string &checkWith);

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
     * @return TF32 
     */
    TF32 randomNumber(const TF32 min, const TF32 max);

    /**
     * @brief generate random number
     * 
     * @param min 
     * @param max 
     * @return TF64 
     */
    TF64 randomNumber(const TF64 min, const TF64 max);

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


namespace string
{
    TBuffer toBuffer(const std::string &input, size_t requiredSize);
} // namespace string


#if LIBPRCPP_USING_JSONCPP
namespace json
{
    /**
     * @brief read json input and convert to string
     * 
     * @param input 
     * @param indent 
     * @param precision 
     * @return std::string 
     */
    std::string toString(const Json::Value &input, const int &indent = 4, const int &precision = 16);

    /**
     * @brief read .csv file and convert to json value
     * 
     * @param csvFilePath 
     * @return Json::Value 
     */
    Json::Value fromCSV(const std::string &csvFilePath);

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

    /**
     * @brief save to .csv from .json file
     * 
     * @param jsonFilePath 
     * @param output 
     * @param indent 
     * @param precision 
     * @return EResult 
     */
    EResult saveToCSV(const std::string &jsonFilePath, const std::string &output);

    /**
     * @brief save json data input to output
     * 
     * @param input 
     * @param output 
     * @param indent default 4
     * @param precision default 16
     * @return EResult 
     */
    EResult saveToJSON(const Json::Value &input, const std::string &output, const int &indent = 4, const int &precision = 16);
} // namespace json
#endif // LIBPRCPP_USING_JSONCPP


namespace read
{
    /**
     * @brief read file as buffer from filePath param
     * 
     * @param filePath 
     * @return TBuffer 
     */
    TBuffer fileAsBuffer(const std::string& filePath);

    /**
     * @brief read path and check that file is exists
     * 
     * @param path 
     * @return true ok
     * @return false fail
     */
    bool fileExists(const std::string &path);
} // namespace read


namespace write
{
    /**
     * @brief write file from buffer
     * 
     * @param filePath 
     * @param bufferData 
     * @return true ok
     * @return false fail
     */
    bool fileFromBuffer(const std::string &filePath, const TBuffer &bufferData);
} // namespace write


} // namespace utilityFunctions
} // namespace libprcpp

#endif // LIBPRCPP_UTILITY_FUNCS_HH
