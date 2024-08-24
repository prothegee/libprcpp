#include "system_module.h"

namespace libprcpp
{

CSystemModule::CSystemModule()
{
}

CSystemModule::~CSystemModule()
{
}

bool CSystemModule::SDirectory::createDirectory(const std::string &path)
{
    std::filesystem::path directory = path;

    return fs::create_directory(directory);
}

bool CSystemModule::SDirectory::deleteDirectory(const std::string &path)
{
    std::filesystem::path directory = path;

    return fs::remove(directory);
}

std::string CSystemModule::SDirectory::getCurrentDir()
{
    std::filesystem::path currentDir = std::filesystem::current_path();

    return currentDir.string();
}

#if LIBPRCPP_PROJECT_USING_LIBHARU
bool CSystemModule::SFilePDF::generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig)
{
    bool result = false;

    HPDF_Doc pdf = HPDF_New(filePDFerrorHandler, NULL);
    if (!pdf)
    {
        std::cerr << "ERROR FilePDF: cannot create PDF object on \"CSystemModule::SFilePDF::generateTable\"\n";
        return result;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, pdfConfig.page_size, pdfConfig.page_direction);

    HPDF_Font font = HPDF_GetFont(pdf, pdfConfig.font.c_str(), NULL);
    HPDF_Page_SetFontAndSize(page, font, 12);

    for (size_t i = 0; i < tableData.size(); ++i)
    {
        for (size_t j = 0; j < tableData[i].size(); ++j)
        {
            float posX = pdfConfig.table_left_x + j * pdfConfig.cell_width;
            float posY = pdfConfig.table_top_y - i * pdfConfig.cell_height;

            HPDF_Page_Rectangle(page, posX, posY - pdfConfig.cell_height, pdfConfig.cell_width, pdfConfig.cell_height);
            HPDF_Page_Stroke(page);

            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, posX + 2, posY - pdfConfig.cell_height + 2, tableData[i][j].c_str());
            HPDF_Page_EndText(page);
        }
    }

    HPDF_SaveToFile(pdf, filePathName.c_str());

    HPDF_Free(pdf);

    result = true;

    #if PROJECT_BUILD_STATUS == 1
    std::cout << "DEBUG FilePDF: generated successfully!\n";
    #endif // PROJECT_BUILD_STATUS

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#if LIBPRCPP_PROJECT_USING_JSONCPP
std::string CSystemModule::SFileJSON::toString(const Json::Value &input, const int &indent, const int &precision)
{
    int _indent, _precision;

    if (indent >= 4) { _indent = 4; }
    if (indent <= 3) { _indent = 0; }
    if (precision >= 16) { _precision = 16; }
    if (precision <= 2) { _precision = 2; }

    Json::StreamWriterBuilder writter;
    
    std::string _indentString = "";
    for (auto i = 0; i < indent; i++)
    {
        _indentString += " ";
    }

    writter.settings_["indentation"] = _indentString;
    writter.settings_["precision"] = _precision;

    return std::string(Json::writeString(writter, input));
}

Json::Value CSystemModule::SFileJSON::fromFile(const std::string &input)
{
    Json::Value result;

    std::ifstream f(input);

    if (f.is_open())
    {
        f >> result;
        f.close();
    }
    else
    {
        std::cerr << "ERROR FileJSON: can't find json file from \"" << input << "\" in \"CSystemModule::SFileJSON::fromFile\"\n";
    }

    return result;
}

Json::Value CSystemModule::SFileJSON::fromString(const std::string &input, const int &indent, const int &precision)
{
    Json::Value result;

    int _indent, _precision;

    if (indent >= 4) { _indent = 4; }
    if (indent <= 3) { _indent = 0; }
    if (precision >= 16) { _precision = 16; }
    if (precision <= 2) { _precision = 2; }

    std::string _indentString = "";
    for (auto i = 0; i < indent; i++)
    {
        _indentString += " ";
    }

    JSONCPP_STRING err;
    Json::CharReaderBuilder builder;

    builder["indentation"] = _indentString;
    builder["precision"] = _precision;

    const int inputLength = static_cast<int>(input.length());

    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    reader->parse(input.c_str(), input.c_str() + inputLength, &result, &err);

    return result;
}

Json::Value CSystemModule::SFileJSON::fromCSV(const std::string &input)
{
    Json::Value result;

    std::ifstream file(input);
    std::string line;
    std::vector<std::string> headers;

    if (file.is_open())
    {
        if (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string header;
            while (std::getline(ss, header, ','))
            {
                header.erase(header.find_last_not_of(" \t\r\n") + 1);
                header.erase(0, header.find_first_not_of(" \t\r\n"));
                headers.push_back(header);
            }
        }

        Json::Value jsonArray(Json::arrayValue);
        while (std::getline(file, line))
        {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            
            std::stringstream ss(line);
            std::string cell;
            Json::Value jsonObject(Json::objectValue);
            size_t headerIndex = 0;
            
            while (std::getline(ss, cell, ','))
            {
                cell.erase(cell.find_last_not_of(" \t\n") + 1);
                cell.erase(0, cell.find_first_not_of(" \t\n"));
                
                if (headerIndex < headers.size())
                {
                    if (internal::isNumber(cell))
                    {
                        try
                        {
                            size_t pos;
                            int intValue = std::stoi(cell, &pos);
                            if (pos == cell.size())
                            {
                                jsonObject[headers[headerIndex]] = intValue;
                            }
                            else
                            {
                                jsonObject[headers[headerIndex]] = std::stod(cell);
                            }
                        }
                        catch (...)
                        {
                            jsonObject[headers[headerIndex]] = cell;
                        }
                    }
                    else
                    {
                        jsonObject[headers[headerIndex]] = cell;
                    }
                }
                headerIndex++;
            }
            jsonArray.append(jsonObject);
        }

        result = jsonArray;

        file.close();
    }
    else
    {
        std::cerr << "ERROR FileJSON: can't open \"" << input << "\"in \"CSystemModule::SFileJSON::fromCSV\"\n";
    }

    return result;
}

bool CSystemModule::SFileJSON::save(const Json::Value & input, const std::string & output)
{
    bool result = false;

    std::ofstream outFile(output);
    if (outFile.is_open())
    {
        Json::StreamWriterBuilder writer;

        writer["indentation"] = "    ";

        std::string jsonString = Json::writeString(writer, input);

        outFile << jsonString;
        outFile.close();

        result = true;
    }
    else
    {
        std::cerr << "ERROR FileJSON: can't save file to \"" << output << "\" in \"CSystemModule::SFileJSON::save\"\n";
    }

    return result;
}
bool CSystemModule::SFileJSON::saveToCSV(const std::string &input, const std::string &output)
{
    bool result = false;

    std::ifstream jsonFile(input);
    if (!jsonFile.is_open())
    {
        std::cerr << "ERROR FileJSON: can't open JSON file \"" << input << "\" in \"CSystemModule::SFileJSON::saveToCSV\"\n";
        return result;
    }

    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonData;
    std::string errs;

    if (!Json::parseFromStream(readerBuilder, jsonFile, &jsonData, &errs))
    {
        std::cerr << "ERROR FileJSON: failed to parse json: \"" << errs << "\" in \"CSystemModule::SFileJSON::saveToCSV(\"\n";
        return result;
    }
    jsonFile.close();

    // Open CSV file for writing
    std::ofstream csvFile(output);
    if (!csvFile.is_open())
    {
        std::cerr << "ERROR FileJSON: can't open CSV file " << output << "\" in \"CSystemModule::SFileJSON::saveToCSV\"\n";
        return result;
    }

    if (jsonData.isArray() && !jsonData.empty())
    {
        // Write CSV header
        const Json::Value& firstObject = jsonData[0];
        for (auto it = firstObject.begin(); it != firstObject.end(); ++it)
        {
            if (it != firstObject.begin())
            {
                csvFile << ",";
            }
            csvFile << it.key().asString();
        }
        csvFile << "\n";

        // Write CSV rows
        for (const auto& obj : jsonData)
        {
            for (auto it = firstObject.begin(); it != firstObject.end(); ++it)
            {
                if (it != firstObject.begin())
                {
                    csvFile << ",";
                }
                csvFile << obj[it.key().asString()].asString();
            }
            csvFile << "\n";
        }

        result = true;
    }
    else
    {
        std::cerr << "ERROR FileJSON: json data is not an array or is empty" << " in \"CSystemModule::SFileJSON::saveToCSV\"\n";
    }
    csvFile.close();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

bool CSystemModule::SFileEncDec::fileEncrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik)
{
    bool result = false;

    auto plaintext = readFile(input);

    if (plaintext.empty())
    {
        std::cerr << "ERROR FileEncDec fileEncrypt: input is empty\n";
        return result;
    }

    switch (encryptDecryptMode)
    {
    #if LIBPRCPP_PROJECT_USING_OPENSSL
        case EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL:
        {
            OpenSSL_add_all_algorithms();
            ERR_load_crypto_strings();

            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = aesEncryptOpenSSL(plaintext, _iv.data(), _ik.data());

            result = writeFile(output, ciphertext);

            EVP_cleanup();
            ERR_free_strings();
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        case EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = aesEncryptCryptoPP(plaintext, _iv.data(), _ik.data());

            result = writeFile(output, ciphertext);
        }
        break;

        case EEncDecMode::Enum::ENC_DEC_MODE_XCHACHA20_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = xChaCha20encryptCryptoPP(plaintext, _iv.data(), _ik.data());

            result = writeFile(output, ciphertext);
        }
        break;

        case EEncDecMode::Enum::ENC_DEC_MODE_RC6_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = rc6encryptCryptoPP(plaintext, _iv.data(), _ik.data());

            result = writeFile(output, ciphertext);
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

        default:
        {
            std::cerr << "ERROR FileEncDec fileEncrypt: encryptDecryptMode is not supported\n";
            abort();
        }
        break;
    }

    return result;
}

bool CSystemModule::SFileEncDec::fileDecrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik)
{
    bool result = false;

    auto ciphertext = readFile(input);

    if (ciphertext.empty())
    {
        std::cerr << "ERROR FileEncDec fileEncrypt: input is empty\n";
        return result;
    }

    switch (encryptDecryptMode)
    {
    #if LIBPRCPP_PROJECT_USING_OPENSSL
        case EEncDecMode::Enum::ENC_DEC_MODE_AES_OPENSSL:
        {
            OpenSSL_add_all_algorithms();
            ERR_load_crypto_strings();

            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = aesDecryptOpenSSL(ciphertext, _iv.data(), _ik.data());

            result = writeFile(output, plaintext);

            EVP_cleanup();
            ERR_free_strings();
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        case EEncDecMode::Enum::ENC_DEC_MODE_AES_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = aesDecryptCryptoPP(ciphertext, _iv.data(), _ik.data());

            result = writeFile(output, plaintext);
        }
        break;

        case EEncDecMode::Enum::ENC_DEC_MODE_XCHACHA20_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = xChaCha20decryptCryptoPP(ciphertext, _iv.data(), _ik.data());

            result = writeFile(output, plaintext);
        }
        break;

        case EEncDecMode::Enum::ENC_DEC_MODE_RC6_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = rc6decryptCryptoPP(ciphertext, _iv.data(), _ik.data());

            result = writeFile(output, plaintext);
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

        default:
        {
            std::cerr << "ERROR FileEncDec fileDecrypt: encryptDecryptMode is not supported\n";
            abort();
        }
        break;
    }

    return result;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::readFile(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file)
    {
        std::cerr << "ERROR FileEncDec readFile: opening file for writing\n";
        return {};
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
    {
        std::cerr << "ERROR FileEncDec readFile: writing to file\n";
        return {};
    }

    return buffer;
}

bool CSystemModule::SFileEncDec::writeFile(const std::string& filePath, const std::vector<unsigned char>& data)
{
    std::ofstream file(filePath, std::ios::binary);

    if (!file)
    {
        std::cerr << "ERROR FileEncDec writeFile: opening file for writing\n";
        return false;
    }

    if (!file.write(reinterpret_cast<const char*>(data.data()), data.size()))
    {
        std::cerr << "ERROR FileEncDec writeFile: writing to file\n";
        return false;
    }

    return true;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::stringToUnsignedChar(const std::string& str, size_t requiredSize)
{
    std::vector<unsigned char> result(str.begin(), str.end());

    if (result.size() > requiredSize)
    {
        result.resize(requiredSize);
    }
    else if (result.size() < requiredSize)
    {
        result.resize(requiredSize, 0x00);
    }

    return result;
}

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::vector<unsigned char> CSystemModule::SFileEncDec::aesEncryptOpenSSL(const std::vector<unsigned char>& plaintext, const unsigned char* iv, const unsigned char* ik)
{
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
    {
        handleOpenSSLError();
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, ik, iv))
    {
        handleOpenSSLError();
    }

    int len;

    std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);

    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size()))
    {
        handleOpenSSLError();
    }

    int ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len)) 
    {
        handleOpenSSLError();
    }

    ciphertext_len += len;

    ciphertext.resize(ciphertext_len);

    EVP_CIPHER_CTX_free(ctx);

    EVP_cleanup();
    ERR_free_strings();

    return ciphertext;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::aesDecryptOpenSSL(const std::vector<unsigned char>& ciphertext, const unsigned char* iv, const unsigned char* ik)
{
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
    {
        handleOpenSSLError();
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, ik, iv))
    {
        handleOpenSSLError();
    }

    int len;

    std::vector<unsigned char> plaintext(ciphertext.size());

    if (1 != EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()))
    {
        handleOpenSSLError();
    }

    int plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len))
    {
        handleOpenSSLError();
    }

    plaintext_len += len;

    plaintext.resize(plaintext_len);

    EVP_CIPHER_CTX_free(ctx);

    EVP_cleanup();
    ERR_free_strings();

    return plaintext;
}

void CSystemModule::SFileEncDec::handleOpenSSLError()
{
    ERR_print_errors_fp(stderr);
    abort();
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::vector<unsigned char> CSystemModule::SFileEncDec::aesEncryptCryptoPP(const std::vector<unsigned char> &plaintext, const unsigned char *iv, const unsigned char *ik)
{
    std::vector<unsigned char> ciphertext;

    try
    {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
        encryption.SetKeyWithIV(ik, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

        CryptoPP::StringSource ss(plaintext.data(), plaintext.size(), true,
            new CryptoPP::StreamTransformationFilter(encryption,
                new CryptoPP::VectorSink(ciphertext)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR FileEncDec aesEncryptCryptoPP: " << e.what() << std::endl;
        abort();
    }

    return ciphertext;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::aesDecryptCryptoPP(const std::vector<unsigned char> &ciphertext, const unsigned char *iv, const unsigned char *ik)
{
    std::vector<unsigned char> plaintext;

    try
    {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;
        decryption.SetKeyWithIV(ik, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

        CryptoPP::StringSource ss(ciphertext.data(), ciphertext.size(), true,
            new CryptoPP::StreamTransformationFilter(decryption,
                new CryptoPP::VectorSink(plaintext)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR FileEncDec aesDecryptCryptoPP: " << e.what() << std::endl;
        abort();
    }

    return plaintext;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::xChaCha20encryptCryptoPP(const std::vector<unsigned char> &plaintext, const unsigned char *iv, const unsigned char *ik)
{
    std::vector<unsigned char> ciphertext;

    try
    {
        CryptoPP::XChaCha20::Encryption encryption;
        encryption.SetKeyWithIV(ik, CryptoPP::XChaCha20::DEFAULT_KEYLENGTH, iv);

        CryptoPP::StringSource ss(plaintext.data(), plaintext.size(), true,
            new CryptoPP::StreamTransformationFilter(encryption,
                new CryptoPP::VectorSink(ciphertext)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR FileEncDec xChaCha20encryptCryptoPP: " << e.what() << std::endl;
        abort();
    }

    return ciphertext;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::xChaCha20decryptCryptoPP(const std::vector<unsigned char> &ciphertext, const unsigned char *iv, const unsigned char *ik)
{
    std::vector<unsigned char> plaintext;

    try
    {
        CryptoPP::XChaCha20::Decryption decryption;
        decryption.SetKeyWithIV(ik, CryptoPP::XChaCha20::DEFAULT_KEYLENGTH, iv);

        CryptoPP::StringSource ss(ciphertext.data(), ciphertext.size(), true,
            new CryptoPP::StreamTransformationFilter(decryption,
                new CryptoPP::VectorSink(plaintext)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR FileEncDec xChaCha20decryptCryptoPP: " << e.what() << std::endl;
        abort();
    }

    return plaintext;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::rc6encryptCryptoPP(const std::vector<unsigned char> &plaintext, const unsigned char *iv, const unsigned char *ik)
{
    std::vector<unsigned char> ciphertext;

    try
    {
        CryptoPP::CBC_Mode<CryptoPP::RC6>::Encryption encryption;
        encryption.SetKeyWithIV(ik, CryptoPP::RC6::DEFAULT_KEYLENGTH, iv);

        CryptoPP::StringSource ss(plaintext.data(), plaintext.size(), true,
            new CryptoPP::StreamTransformationFilter(encryption,
                new CryptoPP::VectorSink(ciphertext)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR FileEncDec rc6encryptCryptoPP: " << e.what() << std::endl;
        abort();
    }

    return ciphertext;
}

std::vector<unsigned char> CSystemModule::SFileEncDec::rc6decryptCryptoPP(const std::vector<unsigned char> &ciphertext, const unsigned char *iv, const unsigned char *ik)
{
    std::vector<unsigned char> plaintext;

    try
    {
        CryptoPP::CBC_Mode<CryptoPP::RC6>::Decryption decryption;
        decryption.SetKeyWithIV(ik, CryptoPP::RC6::DEFAULT_KEYLENGTH, iv);

        CryptoPP::StringSource ss(ciphertext.data(), ciphertext.size(), true,
            new CryptoPP::StreamTransformationFilter(decryption,
                new CryptoPP::VectorSink(plaintext)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << "ERROR FileEncDec rc6decryptCryptoPP: " << e.what() << std::endl;
        abort();
    }

    return plaintext;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
// RESERVED
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

bool CSystemModule::SSystemEnvironment::portIsAvailable(int port)
{
    bool result = false;

#if PROJECT_BUILD_TARGET == 1
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        std::cerr << "ERROR portIsAvailable: Socket creation failed\n";
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
#elif PROJECT_BUILD_TARGET == 2
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "ERROR portIsAvailable: WSAStartup failed\n";
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET) {
        std::cerr << "ERROR portIsAvailable: Socket creation failed\n";
        WSACleanup();
        return false;
    }

    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    int bindResult = bind(sock, (SOCKADDR*)&addr, sizeof(addr));

    closesocket(sock);
    WSACleanup();

    result = bindResult == 0;
#elif PROJECT_BUILD_TARGET == 3
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        std::cerr << "ERROR portIsAvailable: Socket creation failed\n";
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
    std::cerr << "ERROR portIsAvailable: build target is unknown\n";
#endif // #if PROJECT_BUILD_TARGET == 1

    return result;
}

namespace utilityFunctions
{

    namespace directory
    {
        bool createDirectory(const std::string &path)
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.createDirectory(path);
        }

        bool deleteDirectory(const std::string &path)
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.deleteDirectory(path);
        }

        std::string getCurrentDir()
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.getCurrentDir();
        }
    } // namespace directory

    #if LIBPRCPP_PROJECT_USING_LIBHARU
    namespace filePdf
    {
        bool generateTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FilePDF.generateTable(tableData, filePathName, pdfConfig);
        }
    } // namespace filePdf
    #endif // LIBPRCPP_PROJECT_USING_LIBHARU

    #if LIBPRCPP_PROJECT_USING_JSONCPP
    namespace json
    {
        std::string toString(const Json::Value &input, const int &indent, const int &precision)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.toString(input, indent, precision);
        }

        Json::Value fromFile(const std::string &input)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.fromFile(input);
        }

        Json::Value fromString(const std::string &input, const int &indent, const int &precision)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.fromString(input, indent, precision);
        }

        Json::Value fromCSV(const std::string &input)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.fromCSV(input);
        }

        bool save(const Json::Value &input, const std::string &output)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.save(input, output);
        }

        bool saveToCSV(const std::string &input, const std::string &output)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileJSON.saveToCSV(input, output);
        }
    } // namespace json

    namespace fileEncDec
    {
        bool fileEncrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileEncDec.fileEncrypt(encryptDecryptMode, input, output, iv, ik);
        }

        bool fileDecrypt(const EEncDecMode::Enum &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik)
        {
            CSystemModule SYSTEM;
            return SYSTEM.FileEncDec.fileDecrypt(encryptDecryptMode, input, output, iv, ik);
        }
    } // namespace fileEncDec
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

    namespace systemEnvironment
    {
        bool portIsAvailable(int port)
        {
            CSystemModule SYSTEM;
            return SYSTEM.SystemEnvironment.portIsAvailable(port);
        }
    } // namespace systemEnvironment

} // namespace utilityFunctions

} // namespace libprcpp
