#ifndef LIBPRCPP_CRYPTOGRAPHY_MODULE_HH
#define LIBPRCPP_CRYPTOGRAPHY_MODULE_HH
#include <libprcpp/base/config.hh>
#include <libprcpp/constants/string_const.hh>

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
#include <cryptopp/ec2n.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/words.h>

#include <cryptopp/blake2.h>
#include <cryptopp/scrypt.h>
#include <cryptopp/sha.h>
#include <cryptopp/gcm.h>
#include <cryptopp/aes.h>
#include <cryptopp/chacha.h>
#include <cryptopp/rc6.h>
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_ARGON2
#include <argon2.h>
#endif // LIBPRCPP_PROJECT_USING_ARGON2

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>

namespace libprcpp
{

namespace internal
{
#if LIBPRCPP_PROJECT_USING_OPENSSL
    /**
     * @brief regenerate data to hex string
     * 
     * @param data 
     * @param length 
     * @return std::string 
     */
    std::string bytesToHexOpenSSL(const unsigned char *data, size_t length);

    /**
     * @brief regenerate string data to hex string
     * 
     * @param input 
     * @return std::string 
     */
    std::string stringToHexStringOpenSSL(const std::string &input);

    /**
     * @brief get result to custom base 36 with openssl lib
     * 
     * @param input 
     * @return std::string 
     */
    std::string stringToCustomBase36OpenSSL(const std::string &input);

    /**
     * @brief get result from custom base 36 with openssl lib
     * 
     * @param input 
     * @return std::string 
     */
    std::string stringFromCustomBase36OpenSSL(const std::string &input);
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_ARGON2
    /**
     * @brief regenerate vector data to hex string
     * 
     * @param data 
     * @return std::string 
     */
    std::string dataToHexStringArgon2(const std::vector<uint8_t> &data);
#endif // LIBPRCPP_PROJECT_USING_ARGON2
} // namespace internal

/**
 * @brief cryptography module class
 * 
 */
class CCryptographyModule
{
private:
    /* data */

public:
    CCryptographyModule(/* args */);
    ~CCryptographyModule();

    /**
     * @brief hash structure
     * 
     */
    struct SHasher
    {
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha1
         * 
         * @note return length is 40
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha1(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha1
         * 
         * @note return length is 40
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha1OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha224
         * 
         * @note return length is 56
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha224(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha224
         * 
         * @note return length is 56
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha224OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha256
         * 
         * @note return length is 64
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha256(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha256
         * 
         * @note return length is 64
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha256OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha384
         * 
         * @note return length is 96
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha384(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha384
         * 
         * @note return length is 96
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha384OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha512
         * 
         * @note return length is 128
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha512(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha512
         * 
         * @note return length is 128
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha512OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate blake2b
         * 
         * @note return length is 128
         * 
         * @param input 
         * @return std::string 
         */
        std::string blake2b(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief scrypt password hasher using cryptopp
         * 
         * @param input 
         * @param salt 
         * @param computationCost 
         * @param blockSizeCost 
         * @param threadsCost 
         * @param derivedLength 
         * @return std::string 
         */
        std::string scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost = (2<<16), const CryptoPP::word64 &blockSizeCost = 8, const CryptoPP::word64 &threadsCost = 12, const uint32_t &derivedLength = 32);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief scrypt password hasher using OpenSSL
         * 
         * @param input 
         * @param salt 
         * @param computationCost 
         * @param blockSizeCost 
         * @param threadsCost 
         * @param derivedLength 
         * @return std::string 
         */
        std::string scryptOpenSSL(const std::string &input, const std::string &salt, const uint32_t &computationCost = (2<<16), const uint32_t &blockSizeCost = 8, const uint32_t &threadsCost = 12, const uint32_t &derivedLength = 32);
    #endif

    #if LIBPRCPP_PROJECT_USING_ARGON2
        /**
         * @brief argon2 password hasher
         * 
         * @param input 
         * @param salt required at least 16 characters
         * @param computationCost 
         * @param blockSizeCost 
         * @param threadsCost 
         * @param derivedLength 
         * @return std::string 
         */
        std::string argon2(const std::string &input, const std::string &salt, const uint32_t &computationCost = (2<<20), const uint32_t &blockSizeCost = 8, const uint32_t &threadsCost = 12, const uint32_t &derivedLength = 32);
    #endif // LIBPRCPP_PROJECT_USING_ARGON2
    };
    /**
     * @brief hash object access
     * 
     */
    SHasher Hasher = SHasher();

    /**
     * @brief stream cipher structure
     * 
     */
    struct SStreamCipher
    {
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief encrypt input using CBC AES Rijndael stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesEncrypt(const std::string &input, const std::string &iv, const std::string &ik);
        /**
         * @brief decrypt input using CBC AES Rijndael stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesDecrypt(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief encrypt input using AES OpenSSL
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesEncryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik);
        /**
         * @brief decrypt input using AES OpenSSL
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesDecryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief encrypt input using XChaCha20 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 24
         * @param ik ik recomendation length is 32
         * @return std::string 
         */
        std::string xChaCha20encrypt(const std::string &input, const std::string &iv, const std::string &ik);
        /**
         * @brief decrypt input using XChaCha20 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 24
         * @param ik ik recomendation length is 32
         * @return std::string 
         */
        std::string xChaCha20decrypt(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief encrypt input using CBC R6 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string rc6encrypt(const std::string &input, const std::string &iv, const std::string &ik);
        /**
         * @brief encrypt input using CBC R6 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string rc6decrypt(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    };
    /**
     * @brief stream cipher object access
     * 
     */
    SStreamCipher StreamCipher = SStreamCipher();
};

namespace cryptographyFunctions
{
    namespace hasher
    {
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha1
         * 
         * @note return length is 40
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha1(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha1
         * 
         * @note return length is 40
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha1OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha224
         * 
         * @note return length is 56
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha224(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha224
         * 
         * @note return length is 56
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha224OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha256
         * 
         * @note return length is 64
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha256(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha256
         * 
         * @note return length is 64
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha256OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha384
         * 
         * @note return length is 96
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha384(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha384
         * 
         * @note return length is 96
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha384OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate sha512
         * 
         * @note return length is 128
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha512(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief generate sha512
         * 
         * @note return length is 64
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha512OpenSSL(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate blake2b
         * 
         * @note return length is 128
         * 
         * @param input 
         * @return std::string 
         */
        std::string blake2b(const std::string &input);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate scrypt hasher
         * 
         * @param input 
         * @param salt 
         * @param computationCost 
         * @param blockSizeCost 
         * @param threadsCost 
         * @param derivedLength 
         * @return std::string 
         */
        std::string scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost = (2<<16), const CryptoPP::word64 &blockSizeCost = 8, const CryptoPP::word64 &threadsCost = 12, const uint32_t &derivedLength = 32);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief scrypt password hasher using OpenSSL
         * 
         * @param input 
         * @param salt 
         * @param computationCost 
         * @param blockSizeCost 
         * @param threadsCost 
         * @param derivedLength 
         * @return std::string 
         */
        std::string scryptOpenSSL(const std::string &input, const std::string &salt, const uint32_t &computationCost = (2<<16), const uint32_t &blockSizeCost = 8, const uint32_t &threadsCost = 12, const uint32_t &derivedLength = 32);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_ARGON2
        /**
         * @brief argon2 password hasher
         * 
         * @param input 
         * @param salt required at least 16 characters
         * @param computationCost 
         * @param blockSizeCost 
         * @param threadsCost 
         * @param derivedLength 
         * @return std::string 
         */
        std::string argon2(const std::string &input, const std::string &salt, const uint32_t &computationCost = (2<<20), const uint32_t &blockSizeCost = 8, const uint32_t &threadsCost = 12, const uint32_t &derivedLength = 32);
    #endif // LIBPRCPP_PROJECT_USING_ARGON2
    } // namespace hasher

    namespace streamCipher
    {
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief encrypt input using CBC AES Rijndael stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesEncrypt(const std::string &input, const std::string &iv, const std::string &ik);
        /**
         * @brief decrypt input using CBC AES Rijndael stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesDecrypt(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief encrypt input using AES OpenSSL
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesEncryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik);

        /**
         * @brief decrypt input using AES OpenSSL
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesDecryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief encrypt input using XChaCha20 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 24
         * @param ik ik recomendation length is 32
         * @return std::string 
         */
        std::string xChaCha20encrypt(const std::string &input, const std::string &iv, const std::string &ik);
        /**
         * @brief decrypt input using XChaCha20 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 24
         * @param ik ik recomendation length is 32
         * @return std::string 
         */
        std::string xChaCha20decrypt(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief encrypt input using CBC R6 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string rc6encrypt(const std::string &input, const std::string &iv, const std::string &ik);
        /**
         * @brief encrypt input using CBC R6 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string rc6decrypt(const std::string &input, const std::string &iv, const std::string &ik);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    } // namespace streamCipher
} // namespace cryptographyFunctions

} // namespace libprcpp

#endif // LIBPRCPP_CRYPTOGRAPHY_MODULE_HH