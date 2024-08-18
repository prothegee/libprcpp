#ifndef LIBPRCPP_CRYPTOGRAPHY_MODULE_H
#define LIBPRCPP_CRYPTOGRAPHY_MODULE_H
#include <libprcpp/base/config.h>

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

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>

namespace libprcpp
{

/**
 * @brief cryptography module class
 * 
 * @note TODO: split module using OpenSSL lib and CryptoPP lib
 */
class CCryptographyModule
{
private:
    /* data */

public:
    CCryptographyModule(/* args */);
    ~CCryptographyModule();

    struct SHash
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
         * @brief regenerate data to hex string
         * 
         * @param data 
         * @param length 
         * @return std::string 
         */
        std::string bytesToHexOpenSSL(const unsigned char *data, size_t length);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

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
         * @brief generate scrypt hasher default
         * 
         * @param input 
         * @param salt 
         * @param ensureHigh 
         * @return std::string 
         */
        std::string scrypt(const std::string &input, const std::string &salt, const bool &ensureHigh = true);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate scrypt hasher
         * 
         * @param input 
         * @param salt 
         * @param computationCost default: 2 << 16 if !ensureHigh
         * @param blockSizeCost default: 8 if !ensureHigh
         * @param threadsCost default: 1 if !ensureHigh
         * @param derivedLength default: 32
         * @return std::string 
         */
        std::string scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost, const CryptoPP::word64 &blockSizeCost, const CryptoPP::word64 &threadsCost, const uint32_t &derivedLength);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief equivalent to scrypt
         * 
         * @note using OpenSSL lib
         * 
         * @param input 
         * @param salt 
         * @param ensureHigh 
         * @return std::string 
         */
        std::string scryptOpenSSL(const std::string &input, const std::string &salt, const bool &ensureHigh = true);

        std::string toHexaStringOpenSSL(const std::string &input);
    #endif
    };
    SHash Hasher = SHash();

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

        /**
         * @brief get result to custom base 36 with openssl lib
         * 
         * @param input 
         * @return std::string 
         */
        std::string toCustomBase36OpenSSL(const std::string &input);

        /**
         * @brief get result from custom base 36 with openssl lib
         * 
         * @param input 
         * @return std::string 
         */
        std::string fromCustomBase36OpenSSL(const std::string &input);
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
    SStreamCipher StreamCipher = SStreamCipher();
};

namespace utilityFunctions
{

namespace cryptography
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
         * @brief generate scrypt hasher default
         * 
         * @param input 
         * @param salt 
         * @param ensureHigh 
         * @return std::string 
         */
        std::string scrypt(const std::string &input, const std::string &salt, const bool &ensureHigh = true);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        /**
         * @brief generate scrypt hasher
         * 
         * @param input 
         * @param salt 
         * @param computationCost default: 2 << 16 if !ensureHigh
         * @param blockSizeCost default: 8 if !ensureHigh
         * @param threadsCost default: 1 if !ensureHigh
         * @param derivedLength default: 32
         * @return std::string 
         */
        std::string scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost, const CryptoPP::word64 &blockSizeCost, const CryptoPP::word64 &threadsCost, const uint32_t &derivedLength);
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        /**
         * @brief equivalent to scrypt
         * 
         * @note using OpenSSL lib
         * 
         * @param input 
         * @param salt 
         * @param ensureHigh 
         * @return std::string 
         */
        std::string scryptOpenSSL(const std::string &input, const std::string &salt, const bool &ensureHigh = true);
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL
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
} // namespace cryptography

} // namespace utilityFunctions

} // namespace libprcpp

#endif // LIBPRCPP_CRYPTOGRAPHY_MODULE_H
