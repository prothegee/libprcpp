#include <libprcpp/functions/system_funcs.hh>
#include <libprcpp/functions/utility_funcs.hh>
#include <libprcpp/functions/cryptography_funcs.hh>

namespace libprcpp
{
namespace systemFuntions
{


namespace file
{
    EResult encrypt(const EEncDecMode &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik, const size_t &reservedChunkSize)
    {
        EResult result = EResult::RESULT_UNDEFINED;

        TBuffer buffer(reservedChunkSize);
        std::ifstream file(input, std::ios::binary);

        if (!file)
        {
            std::cerr << "encrypt: can't open input file for reading\n";
            return result;
        }

        std::ofstream outFile(output, std::ios::binary);

        if (!outFile)
        {
            std::cerr << "encrypt: can't open output file for writing\n";
            return result;
        }

        switch (encryptDecryptMode)
        {
        #if LIBPRCPP_USING_OPENSSL
            case EEncDecMode::ENC_DEC_MODE_AES_OPENSSL:
            {
                OpenSSL_add_all_algorithms();
                ERR_load_crypto_strings();

                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer encryptedChunk = cryptographyFunctions::streamCipher::aesEncryptToBufferOpenSSL(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(encryptedChunk.data()), encryptedChunk.size()))
                        {
                            std::cerr << "file::encrypt: failed to write encrypted chunk to file for ENC_DEC_MODE_AES_OPENSSL\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;

                EVP_cleanup();
                ERR_free_strings();
            }
            break;
        #endif // LIBPRCPP_USING_OPENSSL

        #if LIBPRCPP_USING_CRYPTOPP_CMAKE
            case EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP:
            {
                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer encryptedChunk = cryptographyFunctions::streamCipher::aesEncryptToBuffer(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(encryptedChunk.data()), encryptedChunk.size()))
                        {
                            std::cerr << "file::encrypt: failed to write encrypted chunk to file for ENC_DEC_MODE_AES_CRYPTOPP\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;
            }
            break;

            case EEncDecMode::ENC_DEC_MODE_XCHACHA20_CRYPTOPP:
            {
                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer encryptedChunk = cryptographyFunctions::streamCipher::xChaCha20EncryptToBuffer(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(encryptedChunk.data()), encryptedChunk.size()))
                        {
                            std::cerr << "file::encrypt: failed to write encrypted chunk to file for ENC_DEC_MODE_XCHACHA20_CRYPTOPP\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;
            }
            break;

            case EEncDecMode::ENC_DEC_MODE_RC6_CRYPTOPP:
            {
                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer encryptedChunk = cryptographyFunctions::streamCipher::rc6encryptToBuffer(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(encryptedChunk.data()), encryptedChunk.size()))
                        {
                            std::cerr << "file::encrypt: failed to write encrypted chunk to file for ENC_DEC_MODE_RC6_CRYPTOPP\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;
            }
            break;
        #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

            default:
            {
                std::cerr << "encryptDecryptMode is not supported\n";
                result = EResult::RESULT_ERROR;
            }
            break;
        }

        return result;
    }

    EResult decrypt(const EEncDecMode & encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik, const size_t &reservedChunkSize)
    {
        EResult result = EResult::RESULT_UNDEFINED;

        TBuffer buffer(reservedChunkSize);
        std::ifstream file(input, std::ios::binary);

        if (!file)
        {
            std::cerr << "encrypt: can't open input file for reading\n";
            return result;
        }

        std::ofstream outFile(output, std::ios::binary);

        if (!outFile)
        {
            std::cerr << "encrypt: can't open output file for writing\n";
            return result;
        }

        switch (encryptDecryptMode)
        {
        #if LIBPRCPP_USING_OPENSSL
            case EEncDecMode::ENC_DEC_MODE_AES_OPENSSL:
            {
                OpenSSL_add_all_algorithms();
                ERR_load_crypto_strings();

                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer decryptedChunk = cryptographyFunctions::streamCipher::aesDecryptToBufferOpenSSL(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(decryptedChunk.data()), decryptedChunk.size()))
                        {
                            std::cerr << "file::decrypt: failed to write decrypted chunk to file ENC_DEC_MODE_AES_OPENSSL\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;

                EVP_cleanup();
                ERR_free_strings();
            }
            break;
        #endif // LIBPRCPP_USING_OPENSSL

        #if LIBPRCPP_USING_CRYPTOPP_CMAKE
            case EEncDecMode::ENC_DEC_MODE_AES_CRYPTOPP:
            {
                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer decryptedChunk = cryptographyFunctions::streamCipher::aesDecryptToBuffer(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(decryptedChunk.data()), decryptedChunk.size()))
                        {
                            std::cerr << "file::decrypt: failed to write decrypted chunk to file ENC_DEC_MODE_AES_CRYPTOPP\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;
            }
            break;

            case EEncDecMode::ENC_DEC_MODE_XCHACHA20_CRYPTOPP:
            {
                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer decryptedChunk = cryptographyFunctions::streamCipher::xChaCha20DecryptToBuffer(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(decryptedChunk.data()), decryptedChunk.size()))
                        {
                            std::cerr << "file::decrypt: failed to write decrypted chunk to file ENC_DEC_MODE_XCHACHA20_CRYPTOPP\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;
            }
            break;

            case EEncDecMode::ENC_DEC_MODE_RC6_CRYPTOPP:
            {
                TBuffer ivBuffer = utilityFunctions::string::toBuffer(iv, 16);
                TBuffer ikBuffer = utilityFunctions::string::toBuffer(ik, 32);

                // perhaps move this to another function?
                while (file)
                {
                    file.read(reinterpret_cast<char*>(buffer.data()), reservedChunkSize);
                    size_t bytesRead = file.gcount();

                    if (bytesRead > 0)
                    {
                        TBuffer decryptedChunk = cryptographyFunctions::streamCipher::rc6decryptToBuffer(
                            TBuffer(buffer.begin(), buffer.begin() + bytesRead), ivBuffer.data(), ikBuffer.data());

                        if (!outFile.write(reinterpret_cast<const char*>(decryptedChunk.data()), decryptedChunk.size()))
                        {
                            std::cerr << "file::decrypt: failed to write decrypted chunk to file ENC_DEC_MODE_RC6_CRYPTOPP\n";
                            return EResult::RESULT_ERROR;
                        }
                    }
                }

                result = EResult::RESULT_OK;
            }
            break;
        #endif // LIBPRCPP_USING_CRYPTOPP_CMAKE

            default:
            {
                std::cerr << "encryptDecryptMode is not supported\n";
                abort();
            }
            break;
        }

        return result;
    }
} // namespace file

namespace SYSENV
{
    bool isPortAvailable(int port)
    {
        bool result = false;

    #if LIBPRCPP_BUILD_TARGET == 1
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        std::cerr << "isPortAvailable: Socket creation failed\n";
        return false;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    int bindResult = bind(sockfd, (sockaddr*)&addr, sizeof(addr));

    close(sockfd);

    result = bindResult == 0;
    #elif LIBPRCPP_BUILD_TARGET == 2
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "isPortAvailable: WSAStartup failed\n";
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        std::cerr << "isPortAvailable: Socket creation failed\n";
        WSACleanup();
        return false;
    }

    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    #if LIBPRCPP_COMPILER_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4242)
    #pragma warning (disable : 4244)
    addr.sin_port = htons(port); // TMP: ignored, figure it out to handle when MAY data loss
    #pragma warning (pop)
    #endif // LIBPRCPP_COMPILER_MSVC

    int bindResult = bind(sock, (SOCKADDR*)&addr, sizeof(addr));

    closesocket(sock);
    WSACleanup();

    result = bindResult == 0;
    #elif LIBPRCPP_BUILD_TARGET == 3
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        std::cerr << "isPortAvailable: Socket creation failed\n";
        return false;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    int bindResult = bind(sockfd, (sockaddr*)&addr, sizeof(addr));

    close(sockfd);

    result = bindResult == 0;
    #else
    std::cerr << "isPortAvailable: build target is unknown\n";
    #endif // #if LIBPRCPP_BUILD_TARGET == 1

    return result;
    }
} // namespace SYSENV


} // namespace systemFuntions
} // namespace libprcpp
