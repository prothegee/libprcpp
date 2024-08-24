#include <libprcpp/modules/system_module.h>

using namespace libprcpp;

int main(int argc, char *argv[])
{
    CSystemModule SYSTEM;

    std::string iv  = "abcdefghijklmnop";
    std::string iv2 = "abcdefghijklmnopqrstuvwx";
    std::string ik  = "abcdefghijklmnopqrstuvwxyz012345";


    std::string fileInRaw = "../../../test/test_file_encdec/file_in.json";

    std::string imgInRaw = "../../../test/test_file_encdec/file_in.png";


    std::string fileOutEnc1 = "../../../test/test_file_encdec/file_out1.enc";
    std::string fileOutDec1 = "../../../test/test_file_encdec/file_out1.dec";
    std::string fileOutEnc2 = "../../../test/test_file_encdec/file_out2.enc";
    std::string fileOutDec2 = "../../../test/test_file_encdec/file_out2.dec";
    std::string fileOutEnc3 = "../../../test/test_file_encdec/file_out3.enc";
    std::string fileOutDec3 = "../../../test/test_file_encdec/file_out3.dec";
    std::string fileOutEnc4 = "../../../test/test_file_encdec/file_out4.enc";
    std::string fileOutDec4 = "../../../test/test_file_encdec/file_out4.dec";

    std::string imgOutEnc1 = "../../../test/test_file_encdec/file_out_enc1.png";
    std::string imgOutDec1 = "../../../test/test_file_encdec/file_out_dec1.png";
    std::string imgOutEnc2 = "../../../test/test_file_encdec/file_out_enc2.png";
    std::string imgOutDec2 = "../../../test/test_file_encdec/file_out_dec2.png";
    std::string imgOutEnc3 = "../../../test/test_file_encdec/file_out_enc3.png";
    std::string imgOutDec3 = "../../../test/test_file_encdec/file_out_dec3.png";
    std::string imgOutEnc4 = "../../../test/test_file_encdec/file_out_enc4.png";
    std::string imgOutDec4 = "../../../test/test_file_encdec/file_out_dec4.png";


#if LIBPRCPP_PROJECT_USING_OPENSSL
    auto encryptOk1 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, fileInRaw, fileOutEnc1, iv, ik);
    auto decryptOk1 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, fileOutEnc1, fileOutDec1, iv, ik);
#endif // LIBPRCPP_PROJECT_USING_OPENSSL
#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    auto encryptOk2 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP, fileInRaw, fileOutEnc2, iv, ik);
    auto decryptOk2 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP, fileOutEnc2, fileOutDec2, iv, ik);
    auto encryptOk3 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, fileInRaw, fileOutEnc3, iv2, ik);
    auto decryptOk3 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, fileOutEnc3, fileOutDec3, iv2, ik);
    auto encryptOk4 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_RC6_CRYPTOPP, fileInRaw, fileOutEnc4, iv, ik);
    auto decryptOk4 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_RC6_CRYPTOPP, fileOutEnc4, fileOutDec4, iv, ik);
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE


#if LIBPRCPP_PROJECT_USING_OPENSSL
    auto imgEncryptOk1 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, imgInRaw, imgOutEnc1, iv, ik);
    auto imgDecryptOk1 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, imgOutEnc1, imgOutDec1, iv, ik);
#endif // LIBPRCPP_PROJECT_USING_OPENSSL
#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    auto imgEncryptOk2 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP, imgInRaw, imgOutEnc2, iv, ik);
    auto imgDecryptOk2 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP, imgOutEnc2, imgOutDec2, iv, ik);
    auto imgEncryptOk3 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, imgInRaw, imgOutEnc3, iv2, ik);
    auto imgDecryptOk3 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_XCHACHA20_CRYPTOPP, imgOutEnc3, imgOutDec3, iv2, ik);
    auto imgEncryptOk4 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP, imgInRaw, imgOutEnc4, iv, ik);
    auto imgDecryptOk4 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP, imgOutEnc4, imgOutDec4, iv, ik);
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE


#if LIBPRCPP_PROJECT_USING_OPENSSL
    if (encryptOk1)
    {
        std::cout << "MESSAGE: encryptOk1 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: encryptOk1 file fail\n";
    }

    if (decryptOk1)
    {
        std::cout << "MESSAGE: decryptOk1 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: decryptOk1 file fail\n";
    }
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    if (encryptOk2)
    {
        std::cout << "MESSAGE: encryptOk2 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: encryptOk2 file fail\n";
    }

    if (decryptOk2)
    {
        std::cout << "MESSAGE: decryptOk2 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: decryptOk2 file fail\n";
    }

    if (encryptOk3)
    {
        std::cout << "MESSAGE: encryptOk3 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: encryptOk3 file fail\n";
    }

    if (decryptOk3)
    {
        std::cout << "MESSAGE: decryptOk3 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: decryptOk3 file fail\n";
    }

    if (encryptOk4)
    {
        std::cout << "MESSAGE: encryptOk4 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: encryptOk4 file fail\n";
    }

    if (decryptOk4)
    {
        std::cout << "MESSAGE: decryptOk4 file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: decryptOk4 file fail\n";
    }
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_OPENSSL
    if (imgEncryptOk1)
    {
        std::cout << "MESSAGE: imgEncryptOk1 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgEncryptOk1 img file fail\n";
    }

    if (imgDecryptOk1)
    {
        std::cout << "MESSAGE: imgDecryptOk1 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgDecryptOk1 img file fail\n";
    }
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    if (imgEncryptOk2)
    {
        std::cout << "MESSAGE: imgEncryptOk2 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgEncryptOk2 img file fail\n";
    }

    if (imgDecryptOk2)
    {
        std::cout << "MESSAGE: imgDecryptOk2 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgDecryptOk2 img file fail\n";
    }

    if (imgEncryptOk3)
    {
        std::cout << "MESSAGE: imgEncryptOk3 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgEncryptOk3 img file fail\n";
    }

    if (imgDecryptOk3)
    {
        std::cout << "MESSAGE: imgDecryptOk3 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgDecryptOk3 img file fail\n";
    }

    if (imgEncryptOk4)
    {
        std::cout << "MESSAGE: imgEncryptOk4 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgEncryptOk4 img file fail\n";
    }

    if (imgDecryptOk4)
    {
        std::cout << "MESSAGE: imgDecryptOk4 img file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: imgDecryptOk4 img file fail\n";
    }
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
}
