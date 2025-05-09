#ifndef LIBPRCPP_CRYPTOGRAPHY_FUNCS_HH
#define LIBPRCPP_CRYPTOGRAPHY_FUNCS_HH
#include <libprcpp/config.hh>
#include <libprcpp/export.hh>
#include <libprcpp/constants/strings_const.hh>
#include <libprcpp/enums/result_enums.hh>
#include <libprcpp/types/base_types.hh>

#if LIBPRCPP_USING_CRYPTOPP_CMAKE
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
#endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_USING_OPENSSL
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#endif // LIBPRCPP_USING_OPENSSL

#if LIBPRCPP_USING_ARGON2
#include <argon2.h>
#endif // LIBPRCPP_USING_ARGON2

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>

namespace libprcpp
{
namespace cryptographyFunctions
{


#if LIBPRCPP_USING_OPENSSL
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
#endif // LIBPRCPP_USING_OPENSSL

#if LIBPRCPP_USING_ARGON2
/**
 * @brief regenerate vector data to hex string
 * 
 * @param data 
 * @return std::string 
 */
std::string dataToHexStringArgon2(const std::vector<uint8_t> &data);
#endif // LIBPRCPP_USING_ARGON2


namespace hasher
{
    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
    /**
     * @brief generate sha1
     * 
     * @note return length is 40
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha1(const std::string &input);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_OPENSSL
    /**
     * @brief generate sha1
     * 
     * @note return length is 40
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha1OpenSSL(const std::string &input);
    #endif // LIBPRCPP_USING_OPENSSL

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
    /**
     * @brief generate sha224
     * 
     * @note return length is 56
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha224(const std::string &input);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_OPENSSL
    /**
     * @brief generate sha224
     * 
     * @note return length is 56
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha224OpenSSL(const std::string &input);
    #endif // LIBPRCPP_USING_OPENSSL

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
    /**
     * @brief generate sha256
     * 
     * @note return length is 64
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha256(const std::string &input);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_OPENSSL
    /**
     * @brief generate sha256
     * 
     * @note return length is 64
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha256OpenSSL(const std::string &input);
    #endif // LIBPRCPP_USING_OPENSSL

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
    /**
     * @brief generate sha384
     * 
     * @note return length is 96
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha384(const std::string &input);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_OPENSSL
    /**
     * @brief generate sha384
     * 
     * @note return length is 96
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha384OpenSSL(const std::string &input);
    #endif // LIBPRCPP_USING_OPENSSL

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
    /**
     * @brief generate sha512
     * 
     * @note return length is 128
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha512(const std::string &input);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_OPENSSL
    /**
     * @brief generate sha512
     * 
     * @note return length is 128
     * 
     * @param input 
     * @return std::string 
     */
    std::string sha512OpenSSL(const std::string &input);
    #endif // LIBPRCPP_USING_OPENSSL

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
    /**
     * @brief generate blake2b
     * 
     * @note return length is 128
     * 
     * @param input 
     * @return std::string 
     */
    std::string blake2b(const std::string &input);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
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
    std::string scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost = (1<<18), const CryptoPP::word64 &blockSizeCost = 2, const CryptoPP::word64 &threadsCost = 1, const uint32_t &derivedLength = 32);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_OPENSSL
    /**
     * @brief scrypt password hasher using OpenSSL
     * 
     * @param input 
     * @param salt 
     * @param computationCost can't exceed than 16384
     * @param blockSizeCost 
     * @param threadsCost 
     * @param derivedLength 
     * @return std::string 
     */
    DEPRECATED("DEPRECATED: use scrypt instead of this, computationCost has exceed num")
    std::string scryptOpenSSL(const std::string &input, const std::string &salt, const uint32_t &computationCost = (1<<15), const uint32_t &blockSizeCost = 2, const uint32_t &threadsCost = 1, const uint32_t &derivedLength = 32);
    #endif

    #if LIBPRCPP_USING_ARGON2
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
    std::string argon2(const std::string &input, const std::string &salt, const uint32_t &computationCost = (1<<20), const uint32_t &blockSizeCost = 2, const uint32_t &threadsCost = 1, const uint32_t &derivedLength = 32);
    #endif // LIBPRCPP_USING_ARGON2
} // namespace hasher


namespace streamCipher
{
    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
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

    /**
     * @brief encrypt buffer using AES to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer aesEncryptToBuffer(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    /**
     * @brief decrypt buffer using AES to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer aesDecryptToBuffer(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_OPENSSL
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
     * @brief encrypt buffer using AES OpenSSL to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer aesEncryptToBufferOpenSSL(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    /**
     * @brief decrypt buffer using AES OpenSSL to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer aesDecryptToBufferOpenSSL(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    #endif // LIBPRCPP_USING_OPENSSL

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
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

    /**
     * @brief encrypt buffer using xChaCha20 to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer xChaCha20EncryptToBuffer(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    /**
     * @brief deecrypt buffer using xChaCha20 to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer xChaCha20DecryptToBuffer(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_USING_CRYPTOPP_CMAKE
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

    /**
     * @brief encrypt buffer using rc6 to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer rc6encryptToBuffer(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    /**
     * @brief deecrypt buffer using rc6 to buffer
     * 
     * @param buffer 
     * @param ivBuffer 
     * @param ikBuffer 
     * @return TBuffer 
     */
    TBuffer rc6decryptToBuffer(const TBuffer &buffer, TUChr *ivBuffer, TUChr *ikBuffer);
    #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE
} // namespace streamCipher


} // namespace cryptographyFunction
} // namespace libprcpp

#endif // LIBPRCPP_CRYPTOGRAPHY_FUNCS_HH
