#include <libprcpp/modules/system_module.h>

using namespace libprcpp;

int main(int argc, char *argv[])
{
    CSystemModule SYSTEM;

    std::string iv = "abcdefghijklmnop";
    std::string ik = "abcdefghijklmnopqrstuvwxyz012345";

    std::string fileInRaw = "../../../test/test_file_encdec/file_in.json";

    std::string imgInRaw = "../../../test/test_file_encdec/file_in.png";

    std::string fileOutEnc1 = "../../../test/test_file_encdec/file_out1.enc";
    std::string fileOutDec1 = "../../../test/test_file_encdec/file_out1.dec";

    std::string imgOutEnc1 = "../../../test/test_file_encdec/file_out_enc1.png";
    std::string imgOutDec1 = "../../../test/test_file_encdec/file_out_dec1.png";

    auto encryptOk1 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, fileInRaw, fileOutEnc1, iv, ik);
    auto decryptOk1 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, fileOutEnc1, fileOutDec1, iv, ik);

    auto imgEncryptOk1 = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, imgInRaw, imgOutEnc1, iv, ik);
    auto imgDecryptOk1 = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL, imgOutEnc1, imgOutDec1, iv, ik);

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
}
