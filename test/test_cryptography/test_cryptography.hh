#ifndef LIBPRCPP_TEST_CRYPTOGRAPHY_HH
#define LIBPRCPP_TEST_CRYPTOGRAPHY_HH
#include <libprcpp/modules/cryptography_module.hh>

using namespace libprcpp;

class CTestCryptography
{
private:
    const std::string m_email = "foo@bar.baz";

    const std::string m_password_salt = "mysalt1234567890";
    const std::string m_password_input = "myspassword123!";

    const std::string m_iv_aes = "Bmw4jqaYDXYfRM2U";
    const std::string m_ik_aes = "aEnxtbRhQDs8sSANAZJcWzXYjAf9GWag";
    const std::string m_iv_rc6 = "kC5m6AGdHWWU9gh7";
    const std::string m_ik_rc6 = "xmLjGz4NRhYWBj2EbvvtyjQPjCyZdJ4y";
    const std::string m_iv_xchacha20 = "HgXSpQdV6Rk2DeGHMT2D4W5a";
    const std::string m_ik_xchacha20 = "FJRCC5rDfQfKMdWz7SF7CrKj6ARGU6Fy";

    const std::string m_secret_message = "a super secret message";

protected:
    /* data */

public:
    CTestCryptography(/* args */) = default;
    ~CTestCryptography() = default;

    void initializeTest()
    {
        CCryptographyModule Cryptography;

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // sha1
        {
            std::cout << "TEST SHA1: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha1(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA1: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        // sha1 OpenSSL
        {
            std::cout << "TEST SHA1 OpenSSL: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha1OpenSSL(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA1 OpenSSL: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // sha224
        {
            std::cout << "TEST SHA224: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha224(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA224: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        // sha224 OpenSSL
        {
            std::cout << "TEST SHA224 OpenSSL: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha224OpenSSL(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA224 OpenSSL: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // sha256
        {
            std::cout << "TEST SHA256: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha256(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA256: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        // sha256 OpenSSL
        {
            std::cout << "TEST SHA256 OpenSSL: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha256OpenSSL(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA256 OpenSSL: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // sha384
        {
            std::cout << "TEST SHA384: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha384(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA384: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        // sha384 OpenSSL
        {
            std::cout << "TEST SHA384 OpenSSL: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha384OpenSSL(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA384 OpenSSL: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // sha512
        {
            std::cout << "TEST SHA512: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha512(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA512: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        // sha512 OpenSSL
        {
            std::cout << "TEST SHA512 OpenSSL: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.sha512OpenSSL(m_email);
            std::cout << result << "\n";

            std::cout << "TEST SHA512 OpenSSL: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // blake2b
        {
            std::cout << "TEST BLAKE2b: with \"" << m_email << "\":\n";

            auto result = Cryptography.Hasher.blake2b(m_email);
            std::cout << result << "\n";

            std::cout << "TEST BLAKE2b: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // scrypt
        {
            auto start = std::chrono::high_resolution_clock::now();

            std::cout << "TEST Scrypt: with \"" << m_password_input << "\" and \"" << m_password_salt << "\":\n";

            auto result = Cryptography.Hasher.scrypt(m_password_input, m_password_salt);
            std::cout << result << "\n";

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;

            std::cout << "TEST Scrypt: finished in " << duration.count() << " seconds\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        // scrypt OpenSSL
        {
            auto start = std::chrono::high_resolution_clock::now();

            std::cout << "TEST Scrypt OpenSSL: with \"" << m_password_input << "\" and \"" << m_password_salt << "\":\n";

            auto result = Cryptography.Hasher.scryptOpenSSL(m_password_input, m_password_salt);
            std::cout << result << "\n";

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;

            std::cout << "TEST Scrypt OpenSSL: finished in " << duration.count() << " seconds\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_ARGON2
        // argon2
        {
            auto start = std::chrono::high_resolution_clock::now();

            std::cout << "TEST argon2: with \"" << m_password_input << "\" and \"" << m_password_salt << "\":\n";

            auto result = Cryptography.Hasher.argon2(m_password_input, m_password_salt);
            std::cout << result << "\n";

            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;

            std::cout << "TEST argon2: finished in " << duration.count() << " seconds\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_ARGON2

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // aes
        {
            std::cout << "TEST AES: with message: \"" << m_secret_message << "\":\n";

            auto enc = Cryptography.StreamCipher.aesEncrypt(m_secret_message, m_iv_aes, m_ik_aes);
            auto dec = Cryptography.StreamCipher.aesDecrypt(enc, m_iv_aes, m_ik_aes);

            std::cout << "encrypted: " << enc << "\n";
            std::cout << "decrypted: " << dec << "\n";

            std::cout << "TEST AES: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        // aes OpenSSL
        {
            std::cout << "TEST AES OpenSSL: with message: \"" << m_secret_message << "\":\n";

            auto enc = Cryptography.StreamCipher.aesEncryptOpenSSL(m_secret_message, m_iv_aes, m_ik_aes);
            auto dec = Cryptography.StreamCipher.aesDecryptOpenSSL(enc, m_iv_aes, m_ik_aes);

            std::cout << "encrypted: " << enc << "\n";
            std::cout << "decrypted: " << dec << "\n";

            std::cout << "TEST AES OpenSSL: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // rc6
        {
            std::cout << "TEST RC6: with message: \"" << m_secret_message << "\":\n";

            auto enc = Cryptography.StreamCipher.rc6encrypt(m_secret_message, m_iv_rc6, m_ik_rc6);
            auto dec = Cryptography.StreamCipher.rc6decrypt(enc, m_iv_rc6, m_ik_rc6);

            std::cout << "encrypted: " << enc << "\n";
            std::cout << "decrypted: " << dec << "\n";

            std::cout << "TEST RC6: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // xchacha20
        {
            std::cout << "TEST XCHACHA20: with message: \"" << m_secret_message << "\":\n";

            auto enc = Cryptography.StreamCipher.xChaCha20encrypt(m_secret_message, m_iv_xchacha20, m_ik_xchacha20);
            auto dec = Cryptography.StreamCipher.xChaCha20decrypt(enc, m_iv_xchacha20, m_ik_xchacha20);

            std::cout << "encrypted: " << enc << "\n";
            std::cout << "decrypted: " << dec << "\n";

            std::cout << "TEST XCHACHA20: finished\n";
            std::cout << "\n";
        }
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    }
};

#endif // LIBPRCPP_TEST_CRYPTOGRAPHY_HH
