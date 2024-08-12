#ifndef LIBPRCPP_SYSTEM_MODULE_H
#define LIBPRCPP_SYSTEM_MODULE_H
#include <libprcpp/base/config.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <thread>
#include <sstream>

#if LIBPRCPP_PROJECT_USING_LIBHARU
#include "hpdf.h"
#include <libprcpp/types/pdf_types.h>
#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#if LIBPRCPP_PROJECT_USING_JSONCPP
#include <jsoncpp/json/json.h>
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

namespace libprcpp
{

namespace internal
{

// check if string index is number
static bool isNumber(const std::string& s)
{
    if (s.empty()) return false;

    std::string::const_iterator it = s.begin();

    if (*it == '-' || *it == '+') ++it;

    bool hasDigits = false;

    while (it != s.end() && std::isdigit(*it))
    {
        hasDigits = true;
        ++it;
    }

    if (it == s.end()) return hasDigits;
    
    if (*it == '.' && ++it != s.end())
    {
        while (it != s.end() && std::isdigit(*it)) ++it;
        return it == s.end() && hasDigits;
    }

    return false;
} // isNumber

} // namespace internal

// file system namespace
namespace fs = std::filesystem;

/**
 * @brief system module class
 * 
 */
class CSystemModule
{
private:
    /* data */

public:
    CSystemModule(/* args */);
    ~CSystemModule();

    /**
     * @brief directory structure
     * 
     */
    struct SDirectory
    {
        /**
         * @brief create directory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return true if ok
         */
        bool createDirectory(const std::string &path);

        /**
         * @brief delete driectory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return true if ok
         */
        bool deleteDirectory(const std::string &path);

        /**
         * @brief get current directory
         * 
         * @note relative from execute-able file
         * 
         * @return std::string 
         */
        std::string getCurrentDir();
    };
    // directory object access
    SDirectory Directory = SDirectory();

#if LIBPRCPP_PROJECT_USING_LIBHARU
    /**
     * @brief file pdf structure
     * 
     */
    struct SFilePDF
    {
        static void filePDFerrorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
        {
            std::cerr << "ERROR FilePDF: error_no=" << error_no << ", detail_no=" << detail_no << "\n";
        }

        /**
         * @brief generate table pdf file
         * 
         * @param tableData 
         * @param filePathName 
         * @param pdfConfig 
         * @return true if ok
         */
        bool generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig);
    };
    // file pdf access
    SFilePDF FilePDF = SFilePDF();
#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#if LIBPRCPP_PROJECT_USING_JSONCPP
    /**
     * @brief file json structure
     * 
     */
    struct SFileJSON
    {
        std::string toString(const Json::Value &input, const int &indent = 4, const int &precision = 16);

        Json::Value fromFile(const std::string &input);

        Json::Value fromString(const std::string &input, const int &indent = 4, const int &precision = 16);

        Json::Value fromCSV(const std::string &input);

        bool save(const Json::Value &input, const std::string &output);

        bool saveToCSV(const std::string &input, const std::string &output);
    };
    // file json access
    SFileJSON FileJSON = SFileJSON();
#endif // LIBPRCPP_PROJECT_USING_JSONCPP
};

namespace utilityFunction
{

    namespace directory
    {
        /**
         * @brief create directory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return true if ok
         */
        bool createDirectory(const std::string &path);

        /**
         * @brief delete driectory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return true if ok
         */
        bool deleteDirectory(const std::string &path);

        /**
         * @brief get current directory
         * 
         * @note relative from execute-able file
         * 
         * @return std::string 
         */
        std::string getCurrentDir();
    } // namespace directory

    #if LIBPRCPP_PROJECT_USING_LIBHARU
    namespace filePdf
    {
        /**
         * @brief generate table pdf file
         * 
         * @param tableData 
         * @param filePathName 
         * @param pdfConfig 
         * @return true if ok
         */
        bool generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig);
    } // namespace filePdf
    #endif // LIBPRCPP_PROJECT_USING_LIBHARU

    #if LIBPRCPP_PROJECT_USING_JSONCPP
    namespace json
    {
        std::string toString(const Json::Value &input, const int &indent = 4, const int &precision = 16);

        Json::Value fromFile(const std::string &input);

        Json::Value fromString(const std::string &input, const int &indent = 4, const int &precision = 16);

        Json::Value fromCSV(const std::string &input);

        bool save(const Json::Value &input, const std::string &output);

        bool saveToCSV(const std::string &input, const std::string &output);
    } // namespace json
    #endif // LIBPRCPP_PROJECT_USING_JSONCPP

} // namespace utilityFunction

} // namespace libprcpp

#endif // LIBPRCPP_SYSTEM_MODULE_H
