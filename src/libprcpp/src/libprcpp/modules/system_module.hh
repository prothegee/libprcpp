#ifndef LIBPRCPP_SYSTEM_MODULE_HH
#define LIBPRCPP_SYSTEM_MODULE_HH
#include <libprcpp/base/config.hh>

#include <libprcpp/enums/encdec_enums.hh>
#include <libprcpp/enums/result_enums.hh>

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
    /**
     * @brief cehck if string index is number
     * 
     * @param input 
     * @return true 
     * @return false 
     */
    bool isNumber(const std::string& input);
} // namespace internal

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
         * @return EResult::Enum
         */
        EResult::Enum createDir(const std::string &path);

        /**
         * @brief delete driectory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return EResult::Enum
         */
        EResult::Enum deleteDir(const std::string &path);

        /**
         * @brief get current directory
         * 
         * @note relative from execute-able file
         * 
         * @return std::string 
         */
        std::string getCurrentDir();
    };
    /**
     * @brief directory access
     * 
     */
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
         * @return EResult::Enum
         */
        EResult::Enum deleteFile(const std::string &filePath);

    #if LIBPRCPP_PROJECT_USING_JSONCPP
        /**
         * @brief json structure
         * 
         */
        struct SJson
        {
            struct SRead
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
                 * @brief read .json file from filepath & pass to jsonData
                 * 
                 * @param filePath location is relative from executeable, e.g. "../path/sub/filename.json"
                 * @param jsonData data to pass
                 * @return EResult::Enum 
                 */
                EResult::Enum fromFileJSON(const std::string &filePath, Json::Value &jsonData);

                /**
                 * @brief read from .csv file to json & pass to jsonData
                 * 
                 * @param filePath 
                 * @param jsonData 
                 * @return EResult::Enum 
                 */
                EResult::Enum fromFileCSV(const std::string &filePath, Json::Value &jsonData);

                /**
                 * @brief read inputString & pass to jsonData
                 * 
                 * @param inputString 
                 * @param jsonData 
                 * @param indent default 4
                 * @param precision default 16
                 * @return EResult::Enum 
                 */
                EResult::Enum fromString(const std::string &inputString, Json::Value &jsonData, const int &indent = 4, const int &precision = 16);
            };
            SRead Read = SRead();

            struct SWrite
            {
                /**
                 * @brief save json data input to output
                 * 
                 * @param input 
                 * @param output 
                 * @param indent default 4
                 * @param precision default 16
                 * @return EResult::Enum 
                 */
                EResult::Enum saveToJSON(const Json::Value &input, const std::string &output, const int &indent = 4, const int &precision = 16);
                
                /**
                 * @brief save to .csv from .json file
                 * 
                 * @param jsonFilePath 
                 * @param output 
                 * @param indent 
                 * @param precision 
                 * @return EResult::Enum 
                 */
                EResult::Enum saveToCSV(const std::string &jsonFilePath, const std::string &output);
            };
            SWrite Write = SWrite();
        };
        /**
         * @brief json file access
         * 
         */
        SJson JSON = SJson();
    #endif // LIBPRCPP_PROJECT_USING_JSONCPP

    #if LIBPRCPP_PROJECT_USING_LIBHARU
        /**
         * @brief pdf file structure
         * 
         */
        struct SPDF
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

            struct SWrite
            {
                /**
                 * @brief write data from table pdf file
                 * 
                 * @note example: test_generate_pdf.cc in test subdir
                 * 
                 * @param tableData 
                 * @param filePathName 
                 * @param pdfConfig 
                 * @return true if ok
                 */
                bool dataToTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig);
            };
            SWrite Write = SWrite();
        };
        /**
         * @brief pdf file access
         * 
         */
        SPDF PDF = SPDF();
    #endif // LIBPRCPP_PROJECT_USING_LIBHARU

    #if LIBPRCPP_PROJECT_USING_OPENSSL || LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief file encrypt decrypt structure
         * 
         */
        struct SEncrypDecrypt
        {
            /**
             * @brief encrypt file
             * 
             * @param encryptDecryptMode 
             * @param input 
             * @param output 
             * @param iv recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 16 length
             * @param ik recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 32 length
             * @return EResult::Enum
             */
            EResult::Enum fileEncrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);

            /**
             * @brief decrypt file
             * 
             * @param encryptDecryptMode 
             * @param input 
             * @param output 
             * @param iv recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 16 length
             * @param ik recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 32 length
             * @return EResult::Enum
             */
            EResult::Enum fileDecrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);
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
        /**
         * @brief file encrypt decrypt access
         * 
         */
        SEncrypDecrypt EncryptDecrypt = SEncrypDecrypt();
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL || LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    };
    /**
     * @brief file access
     * 
     */
    SFile File = SFile();

    /**
     * @brief system environment structure
     * 
     */
    struct SSYSENV
    {
        /**
         * @brief check if port is available on current system
         * 
         * @param port 
         * @return true if available
         */
        bool isPortAvailable(int port);
    };
    /**
     * @brief system environment
     * 
     */
    SSYSENV SYSENV = SSYSENV();
};

namespace systemFunctions
{
    namespace directory
    {
        /**
         * @brief create directory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return EResult::Enum
         */
        EResult::Enum createDir(const std::string &path);

        /**
         * @brief delete driectory
         * 
         * @note relative from execute-able file
         * 
         * @param path 
         * @return EResult::Enum
         */
        EResult::Enum deleteDir(const std::string &path);

        /**
         * @brief get current directory
         * 
         * @note relative from execute-able file
         * 
         * @return std::string 
         */
        std::string getCurrentDir();
    } // namespace directory

    namespace file
    {
        /**
         * @brief delete filePath param
         * 
         * @param filePath 
         * @return EResult::Enum
         */
        EResult::Enum deleteFile(const std::string &filePath);

        namespace json
        {
            namespace read
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
                 * @brief read .json file from filepath & pass to jsonData
                 * 
                 * @param filePath location is relative from executeable, e.g. "../path/sub/filename.json"
                 * @param jsonData data to pass
                 * @return EResult::Enum 
                 */
                EResult::Enum fromFileJSON(const std::string &filePath, Json::Value &jsonData);

                /**
                 * @brief read from .csv file to json & pass to jsonData
                 * 
                 * @param filePath 
                 * @param jsonData 
                 * @return EResult::Enum 
                 */
                EResult::Enum fromFileCSV(const std::string &filePath, Json::Value &jsonData);

                /**
                 * @brief read inputString & pass to jsonData
                 * 
                 * @param inputString 
                 * @param jsonData 
                 * @param indent default 4
                 * @param precision default 16
                 * @return EResult::Enum 
                 */
                EResult::Enum fromString(const std::string &inputString, Json::Value &jsonData, const int &indent = 4, const int &precision = 16);
            } // namespace read

            namespace write
            {
                /**
                 * @brief save json data input to output
                 * 
                 * @param input 
                 * @param output 
                 * @param indent default 4
                 * @param precision default 16
                 * @return EResult::Enum 
                 */
                EResult::Enum saveToJSON(const Json::Value &input, const std::string &output, const int &indent = 4, const int &precision = 16);

                /**
                 * @brief save to .csv from .json file
                 * 
                 * @param jsonFilePath 
                 * @param output 
                 * @param indent 
                 * @param precision 
                 * @return EResult::Enum 
                 */
                EResult::Enum saveToCSV(const std::string &jsonFilePath, const std::string &output);
            } // namespace read
        } // namespace json

        namespace pdf
        {
            namespace write
            {
                /**
                 * @brief write data from table pdf file
                 * 
                 * @note example: test_generate_pdf.cc in test subdir
                 * 
                 * @param tableData 
                 * @param filePathName 
                 * @param pdfConfig 
                 * @return true if ok
                 */
                bool dataToTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig);
            } // namespace write
        } // namespace pdf

        namespace encryptDecrypt
        {
            /**
             * @brief encrypt file
             * 
             * @param encryptDecryptMode 
             * @param input 
             * @param output 
             * @param iv recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 16 length
             * @param ik recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 32 length
             * @return EResult::Enum
             */
            EResult::Enum fileEncrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);

            /**
             * @brief decrypt file
             * 
             * @param encryptDecryptMode 
             * @param input 
             * @param output 
             * @param iv recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 16 length
             * @param ik recomended length: EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL is 32 length
             * @return EResult::Enum
             */
            EResult::Enum fileDecrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik);
        } // namespace encryptDecrypt
    } // namespace file

    // system environment
    namespace sysEnv
    {
        /**
         * @brief check if port is available on current system
         * 
         * @param port 
         * @return true if available
         */
        bool isPortAvailable(int port);
    } // namespace sysEnv
} // namespace systemFunctions

} // namespace libprcpp

#endif // LIBPRCPP_SYSTEM_MODULE_HH
