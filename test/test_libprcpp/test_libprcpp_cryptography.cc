#include <libprcpp/functions/cryptography_funcs.hh>

using namespace libprcpp;

int main()
{
#if LIBPRCPP_PROJECT_USING_OPENSSL && LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    try
    {
        std::printf("start test for test_cryptography\n");

        std::string email = "foo@bar.baz";
        std::string password = "superpassword123";
        std::string passwordSalt = "1289asjd12983y";
        std::string secretMessage = "a super secret message";
        std::string inp1 = secretMessage;
        std::string iv = "abcdefghijklmnop", ivX = "abcdefghijklmnopqrstuvwx";
        std::string ik = "abcdefghijklmnopqrstuvwxyz012345";

        std::printf("sha1:\n- %s\n", cryptographyFunctions::hasher::sha1(email).c_str());

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::printf("sha1OpenSSl:\n- %s\n", cryptographyFunctions::hasher::sha1OpenSSL(email).c_str());
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL
    
        std::printf("sha224:\n- %s\n", cryptographyFunctions::hasher::sha224(email).c_str());

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::printf("sha224OpenSSL:\n- %s\n", cryptographyFunctions::hasher::sha224OpenSSL(email).c_str());
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

        std::printf("sha256:\n- %s\n", cryptographyFunctions::hasher::sha256(email).c_str());

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::printf("sha256OpenSSL:\n- %s\n", cryptographyFunctions::hasher::sha256OpenSSL(email).c_str());
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

        std::printf("sha384:\n- %s\n", cryptographyFunctions::hasher::sha384(email).c_str());

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::printf("sha384OpenSSL:\n- %s\n", cryptographyFunctions::hasher::sha384OpenSSL(email).c_str());
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

        std::printf("sha512:\n- %s\n", cryptographyFunctions::hasher::sha512(email).c_str());

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::printf("sha512OpenSSL:\n- %s\n", cryptographyFunctions::hasher::sha512OpenSSL(email).c_str());
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

        std::printf("blake2b:\n- %s\n", cryptographyFunctions::hasher::blake2b(email).c_str());

    #if LIBPRCPP_PROJECT_USING_ARGON2
        std::printf("argon2:\n- %s\n", cryptographyFunctions::hasher::argon2(password, passwordSalt).c_str()); // arround 6.0 secs
    #endif // LIBPRCPP_PROJECT_USING_ARGON2

        std::printf("scrypt:\n- %s\n", cryptographyFunctions::hasher::scrypt(password, passwordSalt).c_str()); // arround 6.0 secs

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        std::printf("scryptOpenSSL:\n- %s\n", cryptographyFunctions::hasher::scryptOpenSSL(password, passwordSalt).c_str()); // not sure, kinda broken
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

        auto enc1 = cryptographyFunctions::streamCipher::aesEncrypt(inp1, iv, ik);
        auto dec1 = cryptographyFunctions::streamCipher::aesDecrypt(enc1, iv, ik);
        std::printf("enc1 aes:\n- %s\ndec1 aes:\n- %s\n", enc1.c_str(), dec1.c_str());

    #if LIBPRCPP_PROJECT_USING_OPENSSL
        auto enc2 = cryptographyFunctions::streamCipher::aesEncryptOpenSSL(inp1, iv, ik);
        auto dec2 = cryptographyFunctions::streamCipher::aesDecryptOpenSSL(enc2, iv, ik);
        std::printf("enc2 openssl:\n- %s\ndec2 aes openssl:\n- %s\n", enc2.c_str(), dec2.c_str());
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

        auto enc3 = cryptographyFunctions::streamCipher::xChaCha20encrypt(inp1, ivX, ik);
        auto dec3 = cryptographyFunctions::streamCipher::xChaCha20decrypt(enc3, ivX, ik);
        std::printf("enc3 xchacha20:\n- %s\ndec3 xchacha20:\n- %s\n", enc3.c_str(), dec3.c_str());

        auto enc4 = cryptographyFunctions::streamCipher::rc6encrypt(inp1, iv, ik);
        auto dec4 = cryptographyFunctions::streamCipher::rc6decrypt(enc4, iv, ik);
        std::printf("enc4 rc6:\n- %s\ndec4 rc6:\n- %s\n", enc4.c_str(), dec4.c_str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
#endif // LIBPRCPP_PROJECT_USING_OPENSSL && LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    return 0;
}