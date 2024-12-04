#include "system_module.hh"

namespace libprcpp
{

namespace internal
{
    bool isNumber(const std::string& input)
    {
        if (input.empty()) return false;

        std::string::const_iterator it = input.begin();

        if (*it == '-' || *it == '+') ++it;

        bool hasDigits = false;

        while (it != input.end() && std::isdigit(*it))
        {
            hasDigits = true;
            ++it;
        }

        if (it == input.end()) return hasDigits;
        
        if (*it == '.' && ++it != input.end())
        {
            while (it != input.end() && std::isdigit(*it)) ++it;
            return it == input.end() && hasDigits;
        }

        return false;
    }
} // namespace internal

CSystemModule::CSystemModule()
{
}

CSystemModule::~CSystemModule()
{
}

EResult::ENUM CSystemModule::SDirectory::createDir(const std::string &path)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    std::filesystem::path directory = path;

    try
    {
        std::filesystem::create_directory(directory) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR CSystemModule::SDirectory::createDir: " << e.what() << '\n';
        result = EResult::ENUM::RESULT_ERROR;
    }

    return result;
}

EResult::ENUM CSystemModule::SDirectory::deleteDir(const std::string &path)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    std::filesystem::path directory = path;

    try
    {
        std::filesystem::remove(directory) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR CSystemModule::SDirectory::deleteDir: " << e.what() << '\n';
        result = EResult::ENUM::RESULT_ERROR;
    }

    return result;
}

std::string CSystemModule::SDirectory::getCurrentDir()
{
    std::filesystem::path currentDir = std::filesystem::current_path();

    return currentDir.string();
}

EResult::ENUM CSystemModule::SFile::deleteFile(const std::string &filePath)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    std::filesystem::path file = filePath;

    try
    {
        std::filesystem::remove(file) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR CSystemModule::SFile::deleteFile: " << e.what() << '\n';
        result = EResult::ENUM::RESULT_ERROR;
    }

    return result;
}

#if LIBPRCPP_PROJECT_USING_JSONCPP
std::string CSystemModule::SFile::SJson::SRead::toString(const Json::Value &input, const int &indent, const int &precision)
{
    int _indent = indent, _precision = precision;

    if (indent >= 4) { _indent = 4; }
    if (indent <= 3) { _indent = 0; }
    if (precision >= 16) { _precision = 16; }
    if (precision <= 2) { _precision = 2; }

    Json::StreamWriterBuilder writer;
    
    std::string _indentString = "";
    for (auto i = 0; i < _indent; i++)
    {
        _indentString += " ";
    }

    writer.settings_["indentation"] = _indentString;
    writer.settings_["precision"] = _precision;

    return std::string(Json::writeString(writer, input));
}

EResult::ENUM CSystemModule::SFile::SJson::SRead::fromFileJSON(const std::string &filePath, Json::Value &jsonData)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    try
    {
        std::ifstream f(filePath);

        if (f.is_open())
        {
            f >> jsonData;

            result = EResult::ENUM::RESULT_OK;
        }
        else
        {
            result = EResult::ENUM::RESULT_EXISTS_NOT;
        }
        f.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR CSystemModule::SFile::SJson::SRead::fromFile: " << e.what() << '\n';
        result = EResult::ENUM::RESULT_ERROR;
    }

    return result;
}

EResult::ENUM CSystemModule::SFile::SJson::SRead::fromFileCSV(const std::string &filePath, Json::Value &jsonData)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    std::ifstream file(filePath);
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

        jsonData = jsonArray;

        file.close();

        result = EResult::ENUM::RESULT_OK;
    }
    else
    {
        std::cerr << "ERROR: can't open \"" << filePath << "\"in \"CSystemModule::SFile::SJson::SRead::fromFileCSV\"\n";
        result = EResult::ENUM::RESULT_ERROR;
    }

    return result;
}

EResult::ENUM CSystemModule::SFile::SJson::SRead::fromString(const std::string &inputString, Json::Value &jsonData, const int &indent, const int &precision)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    try
    {
        std::string indentString = "";

        int _indent = 0, _precision = 0;

        if (indent >= 4) { _indent = 4; }
        if (indent <= 3) { _indent = 0; }
        if (precision >= 16) { _precision = 16; }
        if (precision <= 2) { _precision = 2; }

        for (auto i = 0; i < _indent; i++)
        {
            indentString += " ";
        }

        JSONCPP_STRING err;
        Json::CharReaderBuilder builder;

        builder.settings_["indentation"] = indentString;
        builder.settings_["precision"] = _precision;

        const int inputLength = static_cast<int>(inputString.length());

        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        
        (reader->parse(inputString.c_str(), inputString.c_str() + inputLength, &jsonData, &err)) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR CSystemModule::SFile::SJson::SRead::fromString: " << e.what() << '\n';
        result = EResult::ENUM::RESULT_ERROR;
    }

    return result;
}

EResult::ENUM CSystemModule::SFile::SJson::SWrite::saveToJSON(const Json::Value &input, const std::string &output, const int &indent, const int &precision)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    int _indent = indent, _precision = precision;

    if (indent >= 4) { _indent = 4; }
    if (indent <= 3) { _indent = 0; }
    if (precision >= 16) { _precision = 16; }
    if (precision <= 2) { _precision = 2; }

    std::string _indentString = "";
    for (auto i = 0; i < _indent; i++)
    {
        _indentString += " ";
    }

    Json::StreamWriterBuilder writer;

    writer.settings_["indentation"] = _indentString;
    writer.settings_["precision"] = _precision;

    std::ofstream outFile(output);

    if (outFile.is_open())
    {
        std::string jsonString = Json::writeString(writer, input);

        outFile << jsonString;
        outFile.close();

        result = EResult::ENUM::RESULT_OK;
    }
    else
    {
        std::cerr << "ERROR: can't save file to \"" << output << "\" in \"CSystemModule::SFile::SJson::SWrite::saveToJSON\"\n";
        result = EResult::ENUM::RESULT_ERROR;
    }

    return result;
}

EResult::ENUM CSystemModule::SFile::SJson::SWrite::saveToCSV(const std::string &jsonFilePath, const std::string &output)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open())
    {
        std::cerr << "ERROR: can't open JSON file \"" << jsonFilePath << "\" in \"CSystemModule::SFile::SJson::SWrite::saveToCSV\"\n";
        result = EResult::ENUM::RESULT_ERROR;
        return result;
    }

    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonData;
    std::string errs;

    if (!Json::parseFromStream(readerBuilder, jsonFile, &jsonData, &errs))
    {
        std::cerr << "ERROR: failed to parse json: \"" << errs << "\" in \"CSystemModule::SFile::SJson::SWrite::saveToCSV\"\n";
        result = EResult::ENUM::RESULT_ERROR;
        return result;
    }
    jsonFile.close();

    // open CSV file for writing
    std::ofstream csvFile(output);
    if (!csvFile.is_open())
    {
        std::cerr << "ERROR: can't open CSV file " << output << "\" in \"CSystemModule::SFile::SJson::SWrite::saveToCSV\"\n";
        result = EResult::ENUM::RESULT_ERROR;
        return result;
    }

    if (jsonData.isArray() && !jsonData.empty())
    {
        // write CSV header
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

        // write CSV rows
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

        result = EResult::ENUM::RESULT_OK;
    }
    else
    {
        std::cerr << "ERROR: json data is not an array or is empty" << " in \"CSystemModule::SFile::SJson::SWrite::saveToCSV\"\n";
        result = EResult::ENUM::RESULT_ERROR;
    }
    csvFile.close();

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_JSONCPP

#if LIBPRCPP_PROJECT_USING_LIBHARU
bool CSystemModule::SFile::SPDF::SWrite::dataToTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig)
{
    bool result = false;

    HPDF_Doc pdf = HPDF_New(SPDF::filePDFerrorHandler, NULL);
    if (!pdf)
    {
        std::cerr << "ERROR: cannot create PDF object on \"CSystemModule::SFile::SPDF::SWrite::dataToTablegenerateTable\"\n";
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
    std::cout << "CSystemModule::SFile::SPDF::SWrite::dataToTable: generated successfully!\n";
    #endif // PROJECT_BUILD_STATUS

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_LIBHARU

#if LIBPRCPP_PROJECT_USING_OPENSSL || LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
EResult::ENUM CSystemModule::SFile::SEncrypDecrypt::fileEncrypt(const EEncDecMode::ENUM &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    auto plaintext = readFile(input);

    if (plaintext.empty())
    {
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::fileEncrypt: input is empty\n";
        return result;
    }

    switch (encryptDecryptMode)
    {
    #if LIBPRCPP_PROJECT_USING_OPENSSL
        case EEncDecMode::ENUM::ENC_DEC_MODE_AES_OPENSSL:
        {
            OpenSSL_add_all_algorithms();
            ERR_load_crypto_strings();

            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = aesEncryptOpenSSL(plaintext, _iv.data(), _ik.data());

            writeFile(output, ciphertext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;

            EVP_cleanup();
            ERR_free_strings();
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        case EEncDecMode::ENUM::ENC_DEC_MODE_AES_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = aesEncryptCryptoPP(plaintext, _iv.data(), _ik.data());

            writeFile(output, ciphertext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
        }
        break;

        case EEncDecMode::ENUM::ENC_DEC_MODE_XCHACHA20_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = xChaCha20encryptCryptoPP(plaintext, _iv.data(), _ik.data());

            writeFile(output, ciphertext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
        }
        break;

        case EEncDecMode::ENUM::ENC_DEC_MODE_RC6_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto ciphertext = rc6encryptCryptoPP(plaintext, _iv.data(), _ik.data());

            writeFile(output, ciphertext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

        default:
        {
            std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::fileEncrypt: encryptDecryptMode is not supported\n";
            result = EResult::ENUM::RESULT_ERROR;
        }
        break;
    }

    return result;
}

EResult::ENUM CSystemModule::SFile::SEncrypDecrypt::fileDecrypt(const EEncDecMode::ENUM & encryptDecryptMode, const std::string & input, const std::string & output, const std::string & iv, const std::string & ik)
{
    EResult::ENUM result = EResult::ENUM::RESULT_UNDEFINED;

    auto ciphertext = readFile(input);

    if (ciphertext.empty())
    {
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::fileDecrypt: input is empty\n";
        return result;
    }

    switch (encryptDecryptMode)
    {
    #if LIBPRCPP_PROJECT_USING_OPENSSL
        case EEncDecMode::ENUM::ENC_DEC_MODE_AES_OPENSSL:
        {
            OpenSSL_add_all_algorithms();
            ERR_load_crypto_strings();

            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = aesDecryptOpenSSL(ciphertext, _iv.data(), _ik.data());

            writeFile(output, plaintext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;

            EVP_cleanup();
            ERR_free_strings();
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL

    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        case EEncDecMode::ENUM::ENC_DEC_MODE_AES_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = aesDecryptCryptoPP(ciphertext, _iv.data(), _ik.data());

            writeFile(output, plaintext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
        }
        break;

        case EEncDecMode::ENUM::ENC_DEC_MODE_XCHACHA20_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = xChaCha20decryptCryptoPP(ciphertext, _iv.data(), _ik.data());

            writeFile(output, plaintext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
        }
        break;

        case EEncDecMode::ENUM::ENC_DEC_MODE_RC6_CRYPTOPP:
        {
            std::vector<unsigned char> _iv = stringToUnsignedChar(iv, 16);
            std::vector<unsigned char> _ik = stringToUnsignedChar(ik, 32);

            auto plaintext = rc6decryptCryptoPP(ciphertext, _iv.data(), _ik.data());

            writeFile(output, plaintext) ? result = EResult::ENUM::RESULT_OK : result = EResult::ENUM::RESULT_ERROR;
        }
        break;
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

        default:
        {
            std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::fileDecrypt: encryptDecryptMode is not supported\n";
            abort();
        }
        break;
    }

    return result;
}

std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::readFile(const std::string &filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file)
    {
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::readFile: opening file for writing\n";
        return {};
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
    {
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::readFile: writing to file\n";
        return {};
    }

    return buffer;
}
bool CSystemModule::SFile::SEncrypDecrypt::writeFile(const std::string &filePath, const std::vector<unsigned char> &data)
{
    std::ofstream file(filePath, std::ios::binary);

    if (!file)
    {
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::writeFile: opening file for writing\n";
        return false;
    }

    if (!file.write(reinterpret_cast<const char*>(data.data()), data.size()))
    {
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::writeFile: writing to file\n";
        return false;
    }

    return true;
}

std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::stringToUnsignedChar(const std::string &str, size_t requiredSize)
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
std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::aesEncryptOpenSSL(const std::vector<unsigned char> &plaintext, const unsigned char *iv, const unsigned char *ik)
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

    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), (int)plaintext.size()))
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

std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::aesDecryptOpenSSL(const std::vector<unsigned char> &ciphertext, const unsigned char *iv, const unsigned char *ik)
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

    if (1 != EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), (int)ciphertext.size()))
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

void CSystemModule::SFile::SEncrypDecrypt::handleOpenSSLError()
{
    ERR_print_errors_fp(stderr);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::aesEncryptCryptoPP(const std::vector<unsigned char> &plaintext, const unsigned char *iv, const unsigned char *ik)
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
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::aesEncryptCryptoPP: " << e.what() << std::endl;
    }

    return ciphertext;
}
std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::aesDecryptCryptoPP(const std::vector<unsigned char> &ciphertext, const unsigned char *iv, const unsigned char *ik)
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
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::aesDecryptCryptoPP: " << e.what() << std::endl;
    }

    return plaintext;
}
std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::xChaCha20encryptCryptoPP(const std::vector<unsigned char> &plaintext, const unsigned char *iv, const unsigned char *ik)
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
        std::cerr << "ERROR CSystemModule::SFile::xChaCha20encryptCryptoPP: " << e.what() << std::endl;
    }

    return ciphertext;
}
std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::xChaCha20decryptCryptoPP(const std::vector<unsigned char> &ciphertext, const unsigned char *iv, const unsigned char *ik)
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
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::xChaCha20decryptCryptoPP: " << e.what() << std::endl;
    }

    return plaintext;
}
std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::rc6encryptCryptoPP(const std::vector<unsigned char> &plaintext, const unsigned char *iv, const unsigned char *ik)
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
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::rc6encryptCryptoPP: " << e.what() << std::endl;
    }

    return ciphertext;
}

std::vector<unsigned char> CSystemModule::SFile::SEncrypDecrypt::rc6decryptCryptoPP(const std::vector<unsigned char> &ciphertext, const unsigned char *iv, const unsigned char *ik)
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
        std::cerr << "ERROR CSystemModule::SFile::SEncrypDecrypt::rc6decryptCryptoPP: " << e.what() << std::endl;
        abort();
    }

    return plaintext;
}
#endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
#endif // LIBPRCPP_PROJECT_USING_OPENSSL || LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE

bool CSystemModule::SSYSENV::isPortAvailable(int port)
{
    bool result = false;

#if PROJECT_BUILD_TARGET == 1
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        std::cerr << "ERROR CSystemModule::SSYSENV::isPortAvailable: Socket creation failed\n";
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
        std::cerr << "ERROR CSystemModule::SSYSENV::isPortAvailable: WSAStartup failed\n";
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        std::cerr << "ERROR CSystemModule::SSYSENV::isPortAvailable: Socket creation failed\n";
        WSACleanup();
        return false;
    }

    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

#if PROJECT_BUILD_COMPILER_ID == 2
    #pragma warning (push)
    #pragma warning (disable : 4242)
    #pragma warning (disable : 4244)
    addr.sin_port = htons(port); // TMP: ignored, figure it out to handle when MAY data loss
    #pragma warning (pop)
#endif // PROJECT_BUILD_COMPILER_ID

    int bindResult = bind(sock, (SOCKADDR*)&addr, sizeof(addr));

    closesocket(sock);
    WSACleanup();

    result = bindResult == 0;
#elif PROJECT_BUILD_TARGET == 3
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        std::cerr << "ERROR CSystemModule::SSYSENV::isPortAvailable: Socket creation failed\n";
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
    std::cerr << "ERROR CSystemModule::SSYSENV::isPortAvailable: build target is unknown\n";
#endif // #if PROJECT_BUILD_TARGET == 1

    return result;
}

namespace systemFunctions
{
    namespace directory
    {
        EResult::ENUM createDir(const std::string &path)
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.createDir(path);
        }

        EResult::ENUM deleteDir(const std::string &path)
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.deleteDir(path);
        }

        std::string getCurrentDir()
        {
            CSystemModule SYSTEM;
            return SYSTEM.Directory.getCurrentDir();
        }
    } // namespace directory

    namespace file
    {
        EResult::ENUM deleteFile(const std::string &filePath)
        {
            CSystemModule SYSTEM;
            return SYSTEM.File.deleteFile(filePath);
        }

        namespace json
        {
            namespace read
            {
                std::string toString(const Json::Value &input, const int &indent, const int &precision)
                {
                    CSystemModule SYSTEM;
                    return SYSTEM.File.JSON.Read.toString(input, indent, precision);
                }

                EResult::ENUM fromFileJSON(const std::string &filePath, Json::Value &jsonData)
                {
                    CSystemModule SYSTEM;
                    return SYSTEM.File.JSON.Read.fromFileJSON(filePath, jsonData);
                }

                EResult::ENUM fromFileCSV(const std::string &filePath, Json::Value &jsonData)
                {
                    CSystemModule SYSTEM;
                    return SYSTEM.File.JSON.Read.fromFileCSV(filePath, jsonData);
                }

                EResult::ENUM fromString(const std::string &inputString, Json::Value &jsonData, const int &indent, const int &precision)
                {
                    CSystemModule SYSTEM;
                    return SYSTEM.File.JSON.Read.fromString(inputString, jsonData, indent, precision);
                }
            } // namespace read

            namespace write
            {
                EResult::ENUM saveToJSON(const Json::Value &input, const std::string &output, const int &indent, const int &precision)
                {
                    CSystemModule SYSTEM;
                    return SYSTEM.File.JSON.Write.saveToJSON(input, output, indent, precision);
                }

                EResult::ENUM saveToCSV(const std::string &jsonFilePath, const std::string &output)
                {
                    CSystemModule SYSTEM;
                    return SYSTEM.File.JSON.Write.saveToCSV(jsonFilePath, output);
                }
            } // namespace read
        } // namespace json

        namespace pdf
        {
            namespace write
            {
                bool dataToTable(const std::vector<std::vector<std::string>> &tableData, const std::string &filePathName, const TPdfConfig &pdfConfig)
                {
                    CSystemModule SYSTEM;
                    return SYSTEM.File.PDF.Write.dataToTable(tableData, filePathName, pdfConfig);
                }
            } // namespace write
        } // namespace pdf

        namespace encryptDecrypt
        {
            EResult::ENUM fileEncrypt(const EEncDecMode::ENUM &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik)
            {
                CSystemModule SYSTEM;
                return SYSTEM.File.EncryptDecrypt.fileEncrypt(encryptDecryptMode, input, output, iv, ik);
            }

            EResult::ENUM fileDecrypt(const EEncDecMode::ENUM &encryptDecryptMode, const std::string &input, const std::string &output, const std::string &iv, const std::string &ik)
            {
                CSystemModule SYSTEM;
                return SYSTEM.File.EncryptDecrypt.fileDecrypt(encryptDecryptMode, input, output, iv, ik);
            }
        } // namespace encryptDecrypt
    } // namespace file

    // system environment
    namespace sysEnv
    {
        bool isPortAvailable(int port)
        {
            CSystemModule SYSTEM;
            return SYSTEM.SYSENV.isPortAvailable(port);
        }
    } // namespace sysEnv
} // namespace systemFunctions

} // namespace libprcpp
