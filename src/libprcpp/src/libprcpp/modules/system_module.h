#ifndef LIBPRCPP_SYSTEM_MODULE_H
#define LIBPRCPP_SYSTEM_MODULE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <thread>

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
};

} // namespace libprcpp

#endif // LIBPRCPP_SYSTEM_MODULE_H
