#ifndef LIBPRCPP_SYSTEM_FUNCS_HH
#define LIBPRCPP_SYSTEM_FUNCS_HH
#include <libprcpp/config.hh>
#include <libprcpp/export.hh>
#include <libprcpp/enums/encdec_enums.hh>
#include <libprcpp/enums/result_enums.hh>

#if LIBPRCPP_USING_OPENSSL
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#endif // LIBPRCPP_USING_OPENSSL

#if LIBPRCPP_USING_CRYPTOPP_CMAKE
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/chacha.h>
#include <cryptopp/rc6.h>
#endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

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
#if LIBPRCPP_BUILD_TARGET == 1
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif LIBPRCPP_BUILD_TARGET == 2
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#elif LIBPRCPP_BUILD_TARGET == 3
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
// nothing to include
#endif // LIBPRCPP_BUILD_TARGET

namespace libprcpp
{
namespace systemFuntions
{


namespace file
{
    #if LIBPRCPP_USING_OPENSSL || LIBPRCPP_USING_CRYPTOPP_CMAKE
    /**
     * @brief encrypt file
     * 
     * @note careful with the the chunk size
     * 
     * @param encryptDecryptMode 
     * @param input 
     * @param output 
     * @param iv recomended length: ENC_DEC_MODE_AES_OPENSSL, ENC_DEC_MODE_AES_CRYPTOPP, ENC_DEC_MODE_RC6_CRYPTOPP is 16 length, ENC_DEC_MODE_XCHACHA20_CRYPTOPP is 24 length
     * @param ik recomended length: ENC_DEC_MODE_AES_OPENSSL, ENC_DEC_MODE_AES_CRYPTOPP, ENC_DEC_MODE_RC6_CRYPTOPP, ENC_DEC_MODE_XCHACHA20_CRYPTOPP is 32 length
     * @param reservedChunkSize 1048576 as 1 Mb
     * @return EResult
     */
    EResult encrypt(const EEncDecMode &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik, const size_t &reservedChunkSize = 1048576);

    /**
     * @brief decrypt file
     * 
     * @note careful with the the chunk size
     * 
     * @param encryptDecryptMode 
     * @param input 
     * @param output 
     * @param iv recomended length: ENC_DEC_MODE_AES_OPENSSL, ENC_DEC_MODE_AES_CRYPTOPP, ENC_DEC_MODE_RC6_CRYPTOPP is 16 length, ENC_DEC_MODE_XCHACHA20_CRYPTOPP is 24 length
     * @param ik recomended length: ENC_DEC_MODE_AES_OPENSSL, ENC_DEC_MODE_AES_CRYPTOPP, ENC_DEC_MODE_RC6_CRYPTOPP, ENC_DEC_MODE_XCHACHA20_CRYPTOPP is 32 length
     * @param reservedChunkSize 1048576 as 1 Mb
     * @return EResult 
     */
    EResult decrypt(const EEncDecMode &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik, const size_t &reservedChunkSize = 1048576);
    #endif // LIBPRCPP_USING_OPENSSL || LIBPRCPP_USING_CRYPTOPP_CMAKE
} // namespace file


namespace SYSENV
{
    /**
     * @brief check if port is available on current system
     * 
     * @param port 
     * @return true if available
     */
    bool isPortAvailable(int port);
} // namespace SYSENV


} // namespace systemFuntions
} // namespace libprcpp

#endif // LIBPRCPP_SYSTEM_FUNCS_HH
