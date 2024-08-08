#ifndef LIBPRCPP_CRYPTOGRAPHY_MODULE_H
#define LIBPRCPP_CRYPTOGRAPHY_MODULE_H
#include <libprcpp/base/config.h>

#if PROJECT_USING_CRYPTOPP_CMAKE
#include <string>

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

namespace libprcpp
{

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

    struct SHash
    {
        /**
         * @brief generate sha1
         * 
         * @note return length is 40
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha1(const std::string &input);

        /**
         * @brief generate sha224
         * 
         * @note return length is 56
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha224(const std::string &input);

        /**
         * @brief generate sha256
         * 
         * @note return length is 64
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha256(const std::string &input);

        /**
         * @brief generate sha384
         * 
         * @note return length is 96
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha384(const std::string &input);

        /**
         * @brief generate sha512
         * 
         * @note return length is 128
         * 
         * @param input 
         * @return std::string 
         */
        std::string sha512(const std::string &input);

        /**
         * @brief generate blake2b
         * 
         * @note return length is 128
         * 
         * @param input 
         * @return std::string 
         */
        std::string blake2b(const std::string &input);

        /**
         * @brief generate scrypt hasher default
         * 
         * @param input 
         * @param salt 
         * @param ensureHigh 
         * @return std::string 
         */
        std::string scrypt(const std::string &input, const std::string &salt, const bool &ensureHigh = true);

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
    };
    SHash Hasher = SHash();

    struct SStreamCipher
    {
        /**
         * @brief encrypt input using CBC AES Rijndael stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesEncrypt(std::string input, std::string iv, std::string ik);
        /**
         * @brief decrypt input using CBC AES Rijndael stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string aesDecrypt(std::string input, std::string iv, std::string ik);

        /**
         * @brief encrypt input using XChaCha20 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 24
         * @param ik ik recomendation length is 32
         * @return std::string 
         */
        std::string xChaCha20encrypt(std::string input, std::string iv, std::string ik);
        /**
         * @brief decrypt input using XChaCha20 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 24
         * @param ik ik recomendation length is 32
         * @return std::string 
         */
        std::string xChaCha20decrypt(std::string input, std::string iv, std::string ik);

        /**
         * @brief encrypt input using CBC R6 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string rc6encrypt(std::string input, std::string iv, std::string ik);
        /**
         * @brief encrypt input using CBC R6 stream cipher
         * 
         * @param input 
         * @param iv iv recomendation length is 16
         * @param ik ik recomendation length is 16 to 32
         * @return std::string 
         */
        std::string rc6decrypt(std::string input, std::string iv, std::string ik);
    };
    SStreamCipher StreamCipher = SStreamCipher();
};

} // namespace libprcpp

#endif // PROJECT_USING_CRYPTOPP_CMAKE

#endif // LIBPRCPP_CRYPTOGRAPHY_MODULE_H
