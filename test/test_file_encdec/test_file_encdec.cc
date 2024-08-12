#include <libprcpp/modules/system_module.h>

using namespace libprcpp;

int main(int argc, char *argv[])
{
    CSystemModule SYSTEM;

    std::string iv = "abcdefghijklmnop";
    std::string ik = "abcdefghijklmnopqrstuvwxyz012345";

    std::string fileInRaw = "../../../test/test_file_encdec/file_in.json";
    std::string fileOutEnc = "../../../test/test_file_encdec/file_out.enc";
    std::string fileOutDec = "../../../test/test_file_encdec/file_out.dec";

    auto encryptOk = SYSTEM.FileEncDec.fileEncrypt(EEncDecMode::Enum::ENC_DEC_MODE_OPENSSL_AES, fileInRaw, fileOutEnc, iv, ik);

    auto decryptOk = SYSTEM.FileEncDec.fileDecrypt(EEncDecMode::Enum::ENC_DEC_MODE_OPENSSL_AES, fileOutEnc, fileOutDec, iv, ik);

    if (encryptOk)
    {
        std::cout << "MESSAGE: encrypt file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: encrypt file fail\n";
    }

    if (decryptOk)
    {
        std::cout << "MESSAGE: decrypt file ok\n";
    }
    else
    {
        std::cout << "MESSAGE: decrypt file fail\n";
    }
}