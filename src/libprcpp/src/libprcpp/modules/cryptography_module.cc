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
