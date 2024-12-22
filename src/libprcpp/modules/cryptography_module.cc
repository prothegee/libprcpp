#include "cryptography_module.hh"

namespace libprcpp
{

namespace internal
{
#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string bytesToHexOpenSSL(const unsigned char *data, size_t length)
{
    std::stringstream ss;

    for (size_t i = 0; i < length; ++i)
    {
        ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }

    return ss.str();
}

std::string stringToHexStringOpenSSL(const std::string &input)
{
    std::string result;

    result.reserve(input.length() * 2);

    for (unsigned char byte : input)
    {
        result.push_back(STRINGS_INTERNAL::HEX_DIGITS[byte >> 4]);
        result.push_back(STRINGS_INTERNAL::HEX_DIGITS[byte & 0x1F]);
    }

    return result;
}

std::string stringToCustomBase36OpenSSL(const std::string &input)
{
    std::string result;

    unsigned int value = 0;
    int bits = 0;

    for (unsigned char byte : input)
    {
        value = (value << 8) | byte;
        bits += 8;

        while (bits >= 5)
        {
            bits -= 5;
            result.push_back(STRINGS_INTERNAL::BASE36_DIGITS[(value >> bits) & 0x1F]); // Mask for 5 bits (0x1F)
        }
    }

    if (bits > 0)
    {
        result.push_back(STRINGS_INTERNAL::BASE36_DIGITS[(value << (5 - bits)) & 0x1F]);
    }

    return result;
}

std::string stringFromCustomBase36OpenSSL(const std::string &input)
{
    std::string result;

    unsigned int value = 0;
    int bits = 0;

    // for (char c : input)
    for (unsigned char c : input)
    {
        size_t index = STRINGS_INTERNAL::BASE36_DIGITS.find(c);
        if (index == std::string::npos)
        {
            std::cerr << "ERROR: Character '" << static_cast<int>(c) << "' not found in base62 character set.\n";
            throw std::runtime_error("Invalid character in input string");
        }

        value = (value << 5) | static_cast<unsigned int>(index);
        bits += 5;

        if (bits >= 8)
        {
            bits -= 8;
            result.push_back((value >> bits) & 0xFF); // Mask for 8 bits (0xFF)
        }
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_ARGON2
std::string dataToHexStringArgon2(const std::vector<uint8_t> &data)
{
    std::string hex_string;
    hex_string.reserve(data.size() * 2);
    for (uint8_t byte : data)
    {
        hex_string.push_back(STRINGS_INTERNAL::HEX_DIGITS[byte >> 4]);
        hex_string.push_back(STRINGS_INTERNAL::HEX_DIGITS[byte & 0x0F]);
    }
    return hex_string;
}
#endif // LIBPRCPP_PROJECT_USING_ARGON2
} // namespace internal

CCryptographyModule::CCryptographyModule()
{
}

CCryptographyModule::~CCryptographyModule()
{
}

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHasher::sha1(const std::string &input)
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

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHasher::sha1OpenSSL(const std::string &input)
{
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    return internal::bytesToHexOpenSSL(hash, SHA_DIGEST_LENGTH);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHasher::sha224(const std::string &input)
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

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHasher::sha224OpenSSL(const std::string &input)
{
    unsigned char hash[SHA224_DIGEST_LENGTH];

    SHA224(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    return internal::bytesToHexOpenSSL(hash, SHA224_DIGEST_LENGTH);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHasher::sha256(const std::string &input)
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
std::string CCryptographyModule::SHasher::sha256OpenSSL(const std::string &input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    return internal::bytesToHexOpenSSL(hash, SHA256_DIGEST_LENGTH);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHasher::sha384(const std::string &input)
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

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHasher::sha384OpenSSL(const std::string &input)
{
    unsigned char hash[SHA384_DIGEST_LENGTH];

    SHA384(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    return internal::bytesToHexOpenSSL(hash, SHA384_DIGEST_LENGTH);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHasher::sha512(const std::string &input)
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
std::string CCryptographyModule::SHasher::sha512OpenSSL(const std::string &input)
{
    unsigned char hash[SHA512_DIGEST_LENGTH];

    SHA512(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    return internal::bytesToHexOpenSSL(hash, SHA512_DIGEST_LENGTH);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SHasher::blake2b(const std::string &input)
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
std::string CCryptographyModule::SHasher::scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost, const CryptoPP::word64 &blockSizeCost, const CryptoPP::word64 &threadsCost, const uint32_t &derivedLength)
{
    std::string result;

    std::string passwd_input(input), salt_input(salt);

    try
    {
        CryptoPP::SecByteBlock derived(derivedLength);

        CryptoPP::Scrypt scrypt;

        CryptoPP::AlgorithmParameters params = 
            CryptoPP::MakeParameters("Cost", computationCost)
            ("BlockSize", blockSizeCost)("Parallelization", threadsCost)
            ("Salt", CryptoPP::ConstByteArrayParameter(
                (const CryptoPP::byte*)&salt_input[0], salt_input.size()));

        scrypt.DeriveKey(derived, derived.size(),
            (const CryptoPP::byte*)&passwd_input[0], passwd_input.size(), params);

        CryptoPP::StringSource(derived, derived.size(), true,
            new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));
    }
    catch(const CryptoPP::Exception &e)
    {
        std::cerr << "ERROR: \"CCryptographyModule::SHasher::scrypt\":\n" << e.what() << '\n';
    }

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CCryptographyModule::SHasher::scryptOpenSSL(const std::string &input, const std::string &salt, const uint32_t &computationCost, const uint32_t &blockSizeCost, const uint32_t &threadsCost, const uint32_t &derivedLength)
{
    std::string result;

    std::string passwd_input(input), salt_input(salt);

    uint32_t computation = computationCost, blockSize = blockSizeCost, threads = threadsCost, derived = derivedLength;

    if (computation >= 16384) // has limit
    {
        computation = 16384;
    }

    std::vector<unsigned char> deriveKey(derived);

#if LIBPRCPP_BUILD_TARGET == 1
    if (EVP_PBE_scrypt(input.c_str(), input.length(), reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(), reinterpret_cast<uint32_t>(computation), blockSize, threads, 0, deriveKey.data(), deriveKey.size()) != 1)
#elif LIBPRCPP_BUILD_TARGET == 2
    if (EVP_PBE_scrypt(input.c_str(), input.length(), reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(), computation, blockSize, threads, 0, deriveKey.data(), deriveKey.size()) != 1)
#elif LIBPRCPP_BUILD_TARGET == 3
    if (EVP_PBE_scrypt(input.c_str(), input.length(), reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(), reinterpret_cast<uint32_t>(computation), blockSize, threads, 0, deriveKey.data(), deriveKey.size()) != 1)
#endif // LIBPRCPP_BUILD_TARGET
    {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("ERROR scryptOpenSSL: deriving key with scrypt\n");
    }

    result = internal::stringToHexStringOpenSSL(std::string(deriveKey.begin(), deriveKey.end()));

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_ARGON2
std::string CCryptographyModule::SHasher::argon2(const std::string &input, const std::string &salt, const uint32_t &computationCost, const uint32_t &blockSizeCost, const uint32_t &threadsCost, const uint32_t &derivedLength)
{
    std::string result;

    std::vector<uint8_t> hash(derivedLength);

    // perform Argon2 hashing
    int status = argon2i_hash_raw(
        blockSizeCost,
        computationCost,
        threadsCost,
        input.data(),
        input.size(),
        salt.data(),
        salt.size(),
        hash.data(),
        hash.size()
    );

    if (status != ARGON2_OK)
    {
        throw std::runtime_error("ERROR argon2: Hashering failed with error code: " + std::to_string(status));
    }

    result = internal::dataToHexStringArgon2(hash);

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SStreamCipher::aesEncrypt(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string tmp, result;

    try
    {
        const size_t ivLength = iv.size();
        const size_t keyLength = ik.size();

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
std::string CCryptographyModule::SStreamCipher::aesDecrypt(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string tmp, result;

    try
    {
        const size_t ivLength = iv.size();
        const size_t keyLength = ik.size();

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

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char *>(input.c_str()), (int)input.size()) != 1)
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

    return internal::stringToCustomBase36OpenSSL(result);
}
std::string CCryptographyModule::SStreamCipher::aesDecryptOpenSSL(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string binary_input = internal::stringFromCustomBase36OpenSSL(input);

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

    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, reinterpret_cast<const unsigned char *>(binary_input.c_str()), (int)binary_input.size()) != 1)
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
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::string CCryptographyModule::SStreamCipher::xChaCha20encrypt(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string tmp, result;

    try
    {
        const size_t ivLength = iv.size();
        const size_t keyLength = ik.size();

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
std::string CCryptographyModule::SStreamCipher::xChaCha20decrypt(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string tmp, result;

    try
    {
        const size_t ivLength = iv.size();
        const size_t keyLength = ik.size();

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
std::string CCryptographyModule::SStreamCipher::rc6encrypt(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string tmp, result;

    try
    {
        const size_t ivLength = iv.size();
        const size_t keyLength = ik.size();

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
std::string CCryptographyModule::SStreamCipher::rc6decrypt(const std::string &input, const std::string &iv, const std::string &ik)
{
    std::string tmp, result;

    try
    {
        const size_t ivLength = iv.size();
        const size_t keyLength = ik.size();

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

namespace cryptographyFunctions
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

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string sha1OpenSSL(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha1OpenSSL(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string sha224(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha224(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string sha224OpenSSL(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha224OpenSSL(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

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

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string sha384OpenSSL(const std::string &input)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.sha384OpenSSL(input);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

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
        std::string scrypt(const std::string &input, const std::string &salt, const CryptoPP::word64 &computationCost, const CryptoPP::word64 &blockSizeCost, const CryptoPP::word64 &threadsCost, const uint32_t &derivedLength)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.scrypt(input, salt, computationCost, blockSizeCost, threadsCost, derivedLength);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::string scryptOpenSSL(const std::string &input, const std::string &salt, const uint32_t &computationCost, const uint32_t &blockSizeCost, const uint32_t &threadsCost, const uint32_t &derivedLength)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.scryptOpenSSL(input, salt, computationCost, blockSizeCost, threadsCost, derivedLength);
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_ARGON2
        std::string argon2(const std::string &input, const std::string &salt, const uint32_t &computationCost, const uint32_t &blockSizeCost, const uint32_t &threadsCost, const uint32_t &derivedLength)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.Hasher.argon2(input, salt, computationCost, blockSizeCost, threadsCost, derivedLength);
        }
    #endif // LIBPRCPP_PROJECT_USING_ARGON2
    } // namespace hasher

    namespace streamCipher
    {
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string aesEncrypt(const std::string &input, const std::string &iv, const std::string &ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.aesEncrypt(input, iv, ik);
        }
        std::string aesDecrypt(const std::string &input, const std::string &iv, const std::string &ik)
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
        std::string xChaCha20encrypt(const std::string &input, const std::string &iv, const std::string &ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.xChaCha20encrypt(input, iv, ik);
        }
        std::string xChaCha20decrypt(const std::string &input, const std::string &iv, const std::string &ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.xChaCha20decrypt(input, iv, ik);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        std::string rc6encrypt(const std::string &input, const std::string &iv, const std::string &ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.rc6encrypt(input, iv, ik);
        }
        std::string rc6decrypt(const std::string &input, const std::string &iv, const std::string &ik)
        {
            CCryptographyModule CRYPTOGRAPHY;
            return CRYPTOGRAPHY.StreamCipher.rc6decrypt(input, iv, ik);
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    } // namespace streamCipher
} // namespace cryptographyFunctions

} // namespace libprcpp
