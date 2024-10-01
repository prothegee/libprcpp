#ifndef LIBPRCPP_SYSTEM_MODULE_HH
#define LIBPRCPP_SYSTEM_MODULE_HH
#include <libprcpp/base/config.hh>

#include <libprcpp/enums/encdec_enums.hh>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <thread>
#include <sstream>
#include <cstring>

// includes os specification
#if PROJECT_BUILD_TARGET == 1
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif PROJECT_BUILD_TARGET == 2
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#elif PROJECT_BUILD_TARGET == 3
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
// nothing to include
#endif // PROJECT_BUILD_TARGET

#if LIBPRCPP_PROJECT_USING_LIBHARU
#include "hpdf.h"
#include <libprcpp/types/pdf_types.hh>
#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#if LIBPRCPP_PROJECT_USING_JSONCPP
#include <json/json.h>
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

#if LIBPRCPP_PROJECT_USING_OPENSSL
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/chacha.h>
#include <cryptopp/rc6.h>
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

namespace libprcpp
{

namespace internal
{

// check if string index is number
static bool isNumber(const std::string& s);

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
        bool createDir(const std::string &path);

        /**
         * @brief delete driectory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return true if ok
         */
        bool deleteDir(const std::string &path);

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

    /**
     * @brief file structure
     * 
     */
    struct SFile
    {
        /**
         * @brief delete filePath param
         * 
         * @param filePath 
         * @return true if ok
         */
        bool deleteFile(const std::string &filePath);
    };
    SFile File = SFile();

#if LIBPRCPP_PROJECT_USING_LIBHARU
    /**
     * @brief file pdf structure
     * 
     */
    struct SFilePDF
    {
    #if PROJECT_BUILD_COMPILER_ID == 1
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #elif PROJECT_BUILD_COMPILER_ID == 2
    // RESERVED
    #elif PROJECT_BUILD_COMPILER_ID == 3
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-parameter"
    #endif
        static void filePDFerrorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
        {
            std::cerr << "ERROR FilePDF: error_no=" << error_no << ", detail_no=" << detail_no << "\n";
        }
    #if PROJECT_BUILD_COMPILER_ID == 1
    #pragma GCC diagnostic pop
    #elif PROJECT_BUILD_COMPILER_ID == 2
    // RESERVED
    #elif PROJECT_BUILD_COMPILER_ID == 3
    // RESERVED
    #pragma clang diagnostic pop
    #endif

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

    /**
     * @brief file encrypt decrypt structure
     * 
     */
    struct SFileEncDec
    {
        /**
         * @brief encrypt file
         * 
         * @param encryptDecryptMode 
         * @param input 
         * @param output 
         * @param iv min is 16 length ( 24 for xChaCha20 )
         * @param ik min is 32 length
         * @return true if ok
         */
        bool fileEncrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);

        /**
         * @brief decrypt file
         * 
         * @param encryptDecryptMode 
         * @param input 
         * @param output 
         * @param iv min is 16 length ( 24 for xChaCha20 )
         * @param ik min is 32 length
         * @return true if ok
         */
        bool fileDecrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);

    protected:
        std::vector<unsigned char> readFile(const std::string& filePath);

        bool writeFile(const std::string& filePath, const std::vector<unsigned char>& data);

        std::vector<unsigned char> stringToUnsignedChar(const std::string& str, size_t requiredSize);

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::vector<unsigned char> aesEncryptOpenSSL(const std::vector<unsigned char>& plaintext, const unsigned char* iv, const unsigned char* ik);

        std::vector<unsigned char> aesDecryptOpenSSL(const std::vector<unsigned char>& ciphertext, const unsigned char* iv, const unsigned char* ik);

        void handleOpenSSLError();
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::vector<unsigned char> aesEncryptCryptoPP(const std::vector<unsigned char>& plaintext, const unsigned char* iv, const unsigned char* ik);

        std::vector<unsigned char> aesDecryptCryptoPP(const std::vector<unsigned char>& ciphertext, const unsigned char* iv, const unsigned char* ik);

        std::vector<unsigned char> xChaCha20encryptCryptoPP(const std::vector<unsigned char>& plaintext, const unsigned char* iv, const unsigned char* ik);

        std::vector<unsigned char> xChaCha20decryptCryptoPP(const std::vector<unsigned char>& ciphertext, const unsigned char* iv, const unsigned char* ik);

        std::vector<unsigned char> rc6encryptCryptoPP(const std::vector<unsigned char>& plaintext, const unsigned char* iv, const unsigned char* ik);

        std::vector<unsigned char> rc6decryptCryptoPP(const std::vector<unsigned char>& ciphertext, const unsigned char* iv, const unsigned char* ik);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    };
    // file encrypt decrypt access
    SFileEncDec FileEncDec = SFileEncDec();

    struct SSystemEnvironment
    {
        /**
         * @brief check if port is avaiable
         * 
         * @param port 
         * @return true if available
         */
        bool portIsAvailable(int port);
    };
    // system environment access
    SSystemEnvironment SystemEnvironment = SSystemEnvironment();
};

namespace utilityFunctions
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
        bool createDir(const std::string &path);

        /**
         * @brief delete driectory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return true if ok
         */
        bool deleteDir(const std::string &path);

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

    namespace fileEncDec
    {
        /**
         * @brief encrypt file
         * 
         * @param encryptDecryptMode 
         * @param input 
         * @param output 
         * @param iv recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 16 length
         * @param ik recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 32 length
         * @return true if ok
         */
        bool fileEncrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);

        /**
         * @brief decrypt file
         * 
         * @param encryptDecryptMode 
         * @param input 
         * @param output 
         * @param iv recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 16 length
         * @param ik recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 32 length
         * @return true if ok
         */
        bool fileDecrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);
    } // namespace fileEncDec

    namespace systemEnvironment
    {
        /**
         * @brief check if port is avaiable
         * 
         * @param port 
         * @return true if available
         */
        bool portIsAvailable(int port);
    } // namespace systemEnvironment

} // namespace utilityFunctions

} // namespace libprcpp

#endif // LIBPRCPP_SYSTEM_MODULE_HH
