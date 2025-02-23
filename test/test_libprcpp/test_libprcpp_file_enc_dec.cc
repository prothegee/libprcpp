#include <libprcpp/functions/system_funcs.hh>

using namespace libprcpp;

int main()
{
    try
    {
        std::string iv  = "abcdefghijklmnop";
        std::string iv2 = "abcdefghijklmnopqrstuvwx";
        std::string ik  = "abcdefghijklmnopqrstuvwxyz012345";


        std::string fileInRaw = "../../../../test/test_libprcpp/file_in.json";
        std::string imgInRaw  = "../../../../test/test_libprcpp/file_in.png";


        std::string fileOutEnc1 = "file_out1_enc.json";
        std::string fileOutDec1 = "file_out1_dec.json";
        std::string fileOutEnc2 = "file_out2_enc.json";
        std::string fileOutDec2 = "file_out2_dec.json";
        std::string fileOutEnc3 = "file_out3_enc.json";
        std::string fileOutDec3 = "file_out3_dec.json";
        std::string fileOutEnc4 = "file_out4_enc.json";
        std::string fileOutDec4 = "file_out4_dec.json";

        std::string imgOutEnc1 = "file_out1_enc.png";
        std::string imgOutDec1 = "file_out1_dec.png";
        std::string imgOutEnc2 = "file_out2_enc.png";
        std::string imgOutDec2 = "file_out2_dec.png";
        std::string imgOutEnc3 = "file_out3_enc.png";
        std::string imgOutDec3 = "file_out3_dec.png";
        std::string imgOutEnc4 = "file_out4_enc.png";
        std::string imgOutDec4 = "file_out4_dec.png";


    #if LIBPRCPP_USING_OPENSSL
        auto encryptOk1 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_AES_OPENSSL,        fileInRaw,    fileOutEnc1, iv,  ik);
        auto decryptOk1 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_AES_OPENSSL,        fileOutEnc1,  fileOutDec1, iv,  ik);
    #endif // LIBPRCPP_USING_OPENSSL
        auto encryptOk2 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP,       fileInRaw,    fileOutEnc2, iv,  ik);
        auto decryptOk2 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP,       fileOutEnc2,  fileOutDec2, iv,  ik);
        auto encryptOk3 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, fileInRaw,    fileOutEnc3, iv2, ik);
        auto decryptOk3 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, fileOutEnc3,  fileOutDec3, iv2, ik);
        auto encryptOk4 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_RC6_CRYPTOPP,       fileInRaw,    fileOutEnc4, iv,  ik);
        auto decryptOk4 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_RC6_CRYPTOPP,       fileOutEnc4,  fileOutDec4, iv,  ik);

    #if LIBPRCPP_USING_OPENSSL
        (encryptOk1 != RESULT_OK)
            ? std::printf("encryptOk1 fail\n")
            : std::printf("encryptOk1 ok\n");
        (decryptOk1 != RESULT_OK)
            ? std::printf("decryptOk1 fail\n")
            : std::printf("decryptOk1 ok\n");
    #endif // LIBPRCPP_USING_OPENSSL
        (encryptOk2 != RESULT_OK)
            ? std::printf("encryptOk2 fail\n")
            : std::printf("encryptOk2 ok\n");
        (decryptOk2 != RESULT_OK)
            ? std::printf("decryptOk2 fail\n")
            : std::printf("decryptOk2 ok\n");
        (encryptOk3 != RESULT_OK)
            ? std::printf("encryptOk3 fail\n")
            : std::printf("encryptOk3 ok\n");
        (decryptOk3 != RESULT_OK)
            ? std::printf("decryptOk3 fail\n")
            : std::printf("decryptOk3 ok\n");
        (encryptOk4 != RESULT_OK)
            ? std::printf("encryptOk4 fail\n")
            : std::printf("encryptOk4 ok\n");
        (decryptOk4 != RESULT_OK)
            ? std::printf("decryptOk4 fail\n")
            : std::printf("decryptOk4 ok\n");


    #if LIBPRCPP_USING_OPENSSL
        auto imgEncryptOk1 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_AES_OPENSSL,        imgInRaw,   imgOutEnc1, iv,  ik);
        auto imgDecryptOk1 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_AES_OPENSSL,        imgOutEnc1, imgOutDec1, iv,  ik);
    #endif // LIBPRCPP_USING_OPENSSL
        auto imgEncryptOk2 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP,       imgInRaw,   imgOutEnc2, iv,  ik);
        auto imgDecryptOk2 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP,       imgOutEnc2, imgOutDec2, iv,  ik);
        auto imgEncryptOk3 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, imgInRaw,   imgOutEnc3, iv2, ik);
        auto imgDecryptOk3 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, imgOutEnc3, imgOutDec3, iv2, ik);
        auto imgEncryptOk4 = systemFuntions::file::encrypt(EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP,       imgInRaw,   imgOutEnc4, iv,  ik);
        auto imgDecryptOk4 = systemFuntions::file::decrypt(EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP,       imgOutEnc4, imgOutDec4, iv,  ik);

    #if LIBPRCPP_USING_OPENSSL
        (imgEncryptOk1 != RESULT_OK)
            ? std::printf("imgEncryptOk1 fail\n")
            : std::printf("imgEncryptOk1 ok\n");
        (imgDecryptOk1 != RESULT_OK)
            ? std::printf("imgDecryptOk1 fail\n")
            : std::printf("imgDecryptOk1 ok\n");
    #endif // LIBPRCPP_USING_OPENSSL
        (imgEncryptOk2 != RESULT_OK)
            ? std::printf("imgEncryptOk2 fail\n")
            : std::printf("imgEncryptOk2 ok\n");
        (imgDecryptOk2 != RESULT_OK)
            ? std::printf("imgDecryptOk2 fail\n")
            : std::printf("imgDecryptOk2 ok\n");
        (imgEncryptOk3 != RESULT_OK)
            ? std::printf("imgEncryptOk3 fail\n")
            : std::printf("imgEncryptOk3 ok\n");
        (imgDecryptOk3 != RESULT_OK)
            ? std::printf("imgDecryptOk3 fail\n")
            : std::printf("imgDecryptOk3 ok\n");
        (imgEncryptOk4 != RESULT_OK)
            ? std::printf("imgEncryptOk4 fail\n")
            : std::printf("imgEncryptOk4 ok\n");
        (imgDecryptOk4 != RESULT_OK)
            ? std::printf("imgDecryptOk4 fail\n")
            : std::printf("imgDecryptOk4 ok\n");
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}