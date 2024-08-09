#include "cryptography_module.h"

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

namespace libprcpp
{

CCryptographyModule::CCryptographyModule()
{
}

CCryptographyModule::~CCryptographyModule()
{
}

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

    return result;
}

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

    return result;
}

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
        std::cerr << e.what() << '\n';
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
        std::cerr << e.what() << '\n';
    }

    return result;
}

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
        std::cerr << e.what() << '\n';
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
        std::cerr << e.what() << '\n';
    }

    return result;
}

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
        std::cerr << e.what() << '\n';
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
        std::cerr << e.what() << '\n';
    }

    return result;
}

} // namespace libprcpp

#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
