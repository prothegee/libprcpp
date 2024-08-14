#include "cryptography_module.h"

namespace libprcpp
{

CCryptographyModule::CCryptographyModule()
{
}

CCryptographyModule::~CCryptographyModule()
{
}

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::sha1(const std::string &input)
{
    std::string result;

    CryptoPP::SHA1 hash;
    CryptoPP::byte digest[CryptoPP::SHA1::DIGESTSIZE];
    CryptoPP::HexEncoder encoder;

    hash.CalculateDigest(digest, (CryptoPP::byte*) input.c_str(), input.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::sha224(const std::string &input)
{
    std::string result;

    CryptoPP::SHA224 hash;
    CryptoPP::byte digest[CryptoPP::SHA224::DIGESTSIZE];
    CryptoPP::HexEncoder encoder;

    hash.CalculateDigest(digest, (CryptoPP::byte*) input.c_str(), input.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::sha256(const std::string &input)
{
    std::string result;

    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::HexEncoder encoder;

    hash.CalculateDigest(digest, (CryptoPP::byte*) input.c_str(), input.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHash::bytesToHexOpenSSL(const unsigned char *data, size_t length)
{
    std::stringstream ss;

    for (size_t i = 0; i < length; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }

    return ss.str();
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHash::sha256OpenSSL(const std::string &input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    return bytesToHexOpenSSL(hash, SHA256_DIGEST_LENGTH);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::sha384(const std::string &input)
{
    std::string result;

    CryptoPP::SHA384 hash;
    CryptoPP::byte digest[CryptoPP::SHA384::DIGESTSIZE];
    CryptoPP::HexEncoder encoder;

    hash.CalculateDigest(digest, (CryptoPP::byte*) input.c_str(), input.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::sha512(const std::string &input)
{
    std::string result;

    CryptoPP::SHA512 hash;
    CryptoPP::byte digest[CryptoPP::SHA512::DIGESTSIZE];
    CryptoPP::HexEncoder encoder;

    hash.CalculateDigest(digest, (CryptoPP::byte*) input.c_str(), input.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHash::sha512OpenSSL(const std::string &input)
{
    unsigned char hash[SHA512_DIGEST_LENGTH];

    SHA512(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    return bytesToHexOpenSSL(hash, SHA512_DIGEST_LENGTH);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::blake2b(const std::string &input)
{
    std::string result;

    CryptoPP::BLAKE2b hash;
    CryptoPP::byte digest[CryptoPP::BLAKE2b::DIGESTSIZE];
    CryptoPP::HexEncoder encoder;

    hash.CalculateDigest(digest, (CryptoPP::byte*)input.c_str(), input.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::scrypt(const std::string &input, const std::string &salt, const bool &ensureHigh)
{
    std::string result;

    std::string passwd_input(input), salt_input(salt);

    CryptoPP::word64 computation, blockSize, threads;

    if (ensureHigh)
    {
        computation=2<<16, blockSize=8, threads=16;
    }
    else
    {
        computation=1<<16, blockSize=6, threads=1;
    }

    try
    {
        CryptoPP::SecByteBlock derived(32);
        CryptoPP::Scrypt scrypt;

        CryptoPP::AlgorithmParameters params = 
            CryptoPP::MakeParameters("Cost", computation)
            ("BlockSize", blockSize)("Parallelization", threads)
            ("Salt", CryptoPP::ConstByteArrayParameter(
                (const CryptoPP::byte*)&salt_input[0], salt_input.size()));

        scrypt.DeriveKey(derived, derived.size(),
            (const CryptoPP::byte*)&passwd_input[0], passwd_input.size(), params);

        CryptoPP::StringSource(derived, derived.size(), true,
            new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception &e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SHash::scrypt\":\n" << e.what() << '\n';
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHash::scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost, const CryptoPP::word64 &blockSizeCost, const CryptoPP::word64 &threadsCost, const uint32_t &derivedLength)
{
    std::string result;

    std::string passwd_input(input), salt_input(salt);

    CryptoPP::word64 computation=computationCost, blockSize=blockSizeCost, threads=threadsCost;

    if (computation <= 0) computation = 1<<16;
    if (blockSize <= 0) blockSize = 8;
    if (threads <= 0) threads = 1;

    uint32_t _derivedLength = derivedLength;

    if (_derivedLength <= 32) _derivedLength = 32;

    try
    {
        CryptoPP::SecByteBlock derived(derivedLength);

        CryptoPP::Scrypt scrypt;

        CryptoPP::AlgorithmParameters params = 
            CryptoPP::MakeParameters("Cost", computation)
            ("BlockSize", blockSize)("Parallelization", threads)
            ("Salt", CryptoPP::ConstByteArrayParameter(
                (const CryptoPP::byte*)&salt_input[0], salt_input.size()));

        scrypt.DeriveKey(derived, derived.size(),
            (const CryptoPP::byte*)&passwd_input[0], passwd_input.size(), params);

        CryptoPP::StringSource(derived, derived.size(), true,
            new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception &e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SHash::scrypt\":\n" << e.what() << '\n';
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHash::scryptOpenSSL(const std::string &input, const std::string &salt, const bool &ensureHigh)
{
    std::string result;

    std::string passwd_input(input), salt_input(salt);

    int computation, blockSize, threads;

    if (ensureHigh)
    {
        computation=16384, blockSize=8, threads=32;
    }
    else
    {
        computation=8192, blockSize=6, threads=16;
    }

    int derivedSize = 32;

    std::vector<unsigned char> deriveKey(derivedSize);

    if (EVP_PBE_scrypt(input.c_str(), input.length(), reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(), computation, blockSize, threads, 0, deriveKey.data(), deriveKey.size()) != 1)
    {
        throw std::runtime_error("ERROR scryptOpenSSL: deriving key with scrypt\n");
    }

    result = toHexaStringOpenSSL(std::string(deriveKey.begin(), deriveKey.end()));

    return result;
}

std::string CCryptographyModule::SHash::toHexaStringOpenSSL(const std::string &input)
{
    std::string result;

    static const char hex_digits[] = "abcdefghijklmnopqestuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    result.reserve(input.length() * 2);

    for (unsigned char byte : input)
    {
        result.push_back(hex_digits[byte >> 4]);
        result.push_back(hex_digits[byte & 0x3E]);
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SStreamCipher::aesEncrypt(std::string input, std::string iv, std::string ik)
{
    std::string tmp, result;

    try
    {
        const int ivLength = iv.size();
        const int keyLength = ik.size();

        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;
        enc.SetKeyWithIV((const CryptoPP::byte*)ik.data(), keyLength, (const CryptoPP::byte*)iv.data(), ivLength);

        CryptoPP::StringSource(input, true, new CryptoPP::StreamTransformationFilter(enc, new CryptoPP::StringSink(tmp)));

        CryptoPP::StringSource(tmp, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SStreamCipher::aesEncrypt\":\n" << e.what() << '\n';
    }

    return result;
}
std::string CCryptographyModule::SStreamCipher::aesDecrypt(std::string input, std::string iv, std::string ik)
{
    std::string tmp, result;

    try
    {
        const int ivLength = iv.size();
        const int keyLength = ik.size();

        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec;
        dec.SetKeyWithIV((const CryptoPP::byte*)ik.data(), keyLength, (const CryptoPP::byte*)iv.data(), ivLength);

        CryptoPP::StringSource(input, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(tmp)));

        CryptoPP::StringSource ssrc(tmp, true, new CryptoPP::StreamTransformationFilter(dec, new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SStreamCipher::aesDecrypt\":\n" << e.what() << '\n';
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SStreamCipher::aesEncryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
    {
        throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::aesEncryptOpenSSL\": failed to create cipher context\n");
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(ik.c_str()), reinterpret_cast<const unsigned char *>(iv.c_str())) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::aesEncryptOpenSSL\": failed to initialize encryption\n");
    }

    int len = 0, ciphertext_len = 0;
    std::vector<unsigned char> ciphertext(input.size() + AES_BLOCK_SIZE);

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char *>(input.c_str()), input.size()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::aesEncryptOpenSSL\": failed to encrypt data\n");
    }
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::aesEncryptOpenSSL\": failed to finalize encryption\n");
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    std::string result(ciphertext.begin(), ciphertext.begin() + ciphertext_len);

    return toCustomBase62OpenSSL(result);
}
std::string CCryptographyModule::SStreamCipher::aesDecryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string binary_input = fromCustomBase62OpenSSL(input);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
    {
        throw std::runtime_error("Failed to create cipher context");
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(ik.c_str()), reinterpret_cast<const unsigned char *>(iv.c_str())) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::aesDecryptOpenSSL\": failed to initialize decryption\n");
    }

    int len = 0, plaintext_len = 0;
    std::vector<unsigned char> plaintext(binary_input.size() + AES_BLOCK_SIZE);

    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, reinterpret_cast<const unsigned char *>(binary_input.c_str()), binary_input.size()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::aesDecryptOpenSSL\": failed to decrypt data\n");
    }
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len) != 1)
    {
        std::cerr << "ERROR \"CCryptographyModule::SStreamCipher::aesDecryptOpenSSL\": EVP_DecryptFinal_ex failed. Error code: " << ERR_get_error() << std::endl;

        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::aesDecryptOpenSSL\": failed to finalize decryption\n");
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    std::string result(plaintext.begin(), plaintext.begin() + plaintext_len);

    return result;
}
std::string CCryptographyModule::SStreamCipher::toCustomBase62OpenSSL(const std::string &input)
{
    std::string result;

    static const char base64digits[] = "abcdefghijklmnopqestuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    int bits = 0;
    unsigned int value = 0;

    for (unsigned char byte : input)
    {
        value = (value << 8) | byte;
        bits += 8;

        while (bits >= 6)
        {
            bits -= 6;
            result.push_back(base64digits[(value >> bits) & 0x3F]); // mask for 6 bits (0x3F)
        }
    }

    if (bits > 0)
    {
        result.push_back(base64digits[(value << (6 - bits)) & 0x3F]);
    }

    return result;
}
std::string CCryptographyModule::SStreamCipher::fromCustomBase62OpenSSL(const std::string &input)
{
    std::string result;

    static const std::string base64digits = "abcdefghijklmnopqestuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    int bits = 0;
    unsigned int value = 0;

    for (char c : input)
    {
        int index = base64digits.find(c);
        if (index == std::string::npos)
        {
            throw std::runtime_error("ERROR \"CCryptographyModule::SStreamCipher::fromCustomBase62OpenSSL\": invalid character in input string\n");
        }

        bits += 6;
        value = (value << 6) | index;

        if (bits >= 8)
        {
            bits -= 8;
            result.push_back((value >> bits) & 0xFF); // mask for 8 bits (0xFF)
        }
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SStreamCipher::xChaCha20encrypt(std::string input, std::string iv, std::string ik)
{
    std::string tmp, result;

    try
    {
        const int ivLength = iv.size();
        const int keyLength = ik.size();

        CryptoPP::XChaCha20::Encryption enc;
        enc.SetKeyWithIV((const CryptoPP::byte*)ik.data(), keyLength, (const CryptoPP::byte*)iv.data(), ivLength);

        CryptoPP::StringSource(input, true, new CryptoPP::StreamTransformationFilter(enc, new CryptoPP::StringSink(tmp)));

        CryptoPP::StringSource(tmp, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SStreamCipher::xChacha20encrypt\":\n" << e.what() << '\n';
    }

    return result;
}
std::string CCryptographyModule::SStreamCipher::xChaCha20decrypt(std::string input, std::string iv, std::string ik)
{
    std::string tmp, result;

    try
    {
        const int ivLength = iv.size();
        const int keyLength = ik.size();

        CryptoPP::XChaCha20::Decryption dec;
        dec.SetKeyWithIV((const CryptoPP::byte*)ik.data(), keyLength, (const CryptoPP::byte*)iv.data(), ivLength);

        CryptoPP::StringSource(input, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(tmp)));

        CryptoPP::StringSource ssrc(tmp, true, new CryptoPP::StreamTransformationFilter(dec, new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SStreamCipher::xChaCha20decrypt\":\n" << e.what() << '\n';
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SStreamCipher::rc6encrypt(std::string input, std::string iv, std::string ik)
{
    std::string tmp, result;

    try
    {
        const int ivLength = iv.size();
        const int keyLength = ik.size();

        CryptoPP::CBC_Mode<CryptoPP::RC6>::Encryption enc;
        enc.SetKeyWithIV((const CryptoPP::byte*)ik.data(), keyLength, (const CryptoPP::byte*)iv.data(), ivLength);

        CryptoPP::StringSource(input, true, new CryptoPP::StreamTransformationFilter(enc, new CryptoPP::StringSink(tmp)));

        CryptoPP::StringSource(tmp, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SStreamCipher::rc6encrypt\":\n" << e.what() << '\n';
    }

    return result;
}
std::string CCryptographyModule::SStreamCipher::rc6decrypt(std::string input, std::string iv, std::string ik)
{
    std::string tmp, result;

    try
    {
        const int ivLength = iv.size();
        const int keyLength = ik.size();

        CryptoPP::CBC_Mode<CryptoPP::RC6>::Decryption dec;
        dec.SetKeyWithIV((const CryptoPP::byte*)ik.data(), keyLength, (const CryptoPP::byte*)iv.data(), ivLength);

        CryptoPP::StringSource(input, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(tmp)));

        CryptoPP::StringSource ssrc(tmp, true, new CryptoPP::StreamTransformationFilter(dec, new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SStreamCipher::rc6decrypt\":\n" << e.what() << '\n';
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

namespace utilityFunctions
{
namespace cryptography
{
    namespace hasher
    {
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string sha1(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha1(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string sha224(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha224(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string sha256(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha256(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string sha256OpenSSL(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha256OpenSSL(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string sha384(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha384(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string sha512(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha512(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string sha512OpenSSL(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha512OpenSSL(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string blake2b(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.blake2b(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string scrypt(const std::string &input, const std::string &salt, const bool &ensureHigh)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.scrypt(input, salt, ensureHigh);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost, const CryptoPP::word64 &blockSizeCost, const CryptoPP::word64 &threadsCost, const uint32_t &derivedLength)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.scrypt(input, salt, computationCost, blockSizeCost, threadsCost, derivedLength);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string scryptOpenSSL(const std::string &input, const std::string &salt, const bool &ensureHigh)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.scryptOpenSSL(input, salt, ensureHigh);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL
    } // namespace hasher

    namespace streamCipher
    {
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string aesEncrypt(std::string input, std::string iv, std::string ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.aesEncrypt(input, iv, ik);
        }
        std::string aesDecrypt(std::string input, std::string iv, std::string ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.aesDecrypt(input, iv, ik);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string aesEncryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.aesEncryptOpenSSL(input, iv, ik);
        }

        std::string aesDecryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.aesDecryptOpenSSL(input, iv, ik);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string xChaCha20encrypt(std::string input, std::string iv, std::string ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.xChaCha20encrypt(input, iv, ik);
        }
        std::string xChaCha20decrypt(std::string input, std::string iv, std::string ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.xChaCha20decrypt(input, iv, ik);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string rc6encrypt(std::string input, std::string iv, std::string ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.rc6encrypt(input, iv, ik);
        }
        std::string rc6decrypt(std::string input, std::string iv, std::string ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.rc6decrypt(input, iv, ik);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    } // namespace streamCipher

} // namespace cryptography
} // namespace utilityFunctions

} // namespace libprcpp
