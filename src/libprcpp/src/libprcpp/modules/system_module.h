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

#if PROJECT_USING_LIBHARU
#include "hpdf.h"
#include <libprcpp/types/pdf_types.h>
#endif // PROJECT_USING_LIBHARU

namespace libprcpp
{

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

#if PROJECT_USING_LIBHARU
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

        bool generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig);
    };
    // file pdf access
    SFilePDF FilePDF = SFilePDF();
#endif // PROJECT_USING_LIBHARU
};

} // namespace libprcpp

#endif // LIBPRCPP_SYSTEM_MODULE_H
