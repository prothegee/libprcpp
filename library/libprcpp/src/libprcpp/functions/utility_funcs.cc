#include <libprcpp/functions/utility_funcs.hh>

#if LIBPRCPP_COMPILER_MSVC
#pragma warning (push)
#pragma warning (disable : 4244)
#endif // LIBPRCPP_COMPILER_MSVC

namespace libprcpp
{
namespace utilityFunctions
{

bool isNumeric(const std::string &input)
{
    return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string base64encode(const std::string &input)
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input.c_str(), (int)input.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    std::string result(bufferPtr->data, bufferPtr->length);

    BIO_free_all(bio);
    BIO_free_all(b64);

    return result;
}

std::string base64decode(const std::string &input)
{
    BIO *bio, *b64;

    bio = BIO_new_mem_buf(input.c_str(), -1);
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    char* output = new char[input.size()];

    int decodedLength = BIO_read(bio, output, (int)input.size());

    BIO_free_all(bio);
    BIO_free_all(b64);

    std::string result(output, decodedLength);

    delete[] output;

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL


namespace arg
{
} // namespace arg


namespace find
{
    int eachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords)
    {
        int result = 0;

        for (auto &keyword : keywords)
        {
            if (source.find(keyword) != std::string::npos)
            {
                result += 1;
                foundKeywords.emplace_back(keyword);
            }
        }

        return result;
    }

    bool andReplaceAll(std::string &source, const std::string &query, const std::string &replacement)
    {
        try
        {
            size_t position = 0;

            while ((position = source.find(query, position)) != std::string::npos)
            {
                source.replace(position, query.size(), replacement);
                position += replacement.size();
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    bool keywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction)
    {
        bool result = false;

        size_t beforePos = source.find(keywordBefore);

        if (beforePos != std::string::npos)
        {
            std::string beforeStr = source.substr(0, beforePos);

            if (beforeStr.find(keywordBefore) != std::string::npos)
            {
                extraction = keywordBefore;
                result = true;
            }
        }

        return result;
    }

    bool inputEndsWith(const std::string &input, const std::string &checkWith)
    {
        if (input.length() < checkWith.length())
        {
            return false;
        }
        return input.compare(input.length() - checkWith.length(), checkWith.length(), checkWith) == 0;
    }

    bool keywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction)
    {
        bool result = false;

        size_t afterPos = source.find(keywordAfter);

        if (afterPos != std::string::npos)
        {
            extraction = source.substr(afterPos + 1);
            result = true;
        }

        return result;
    }
} // namespace find


namespace generate
{
    int randomNumber(const int min, const int max)
    {
        int result;

        std::random_device rd;
        std::default_random_engine re(rd());

        std::uniform_int_distribution<int> distribute(min, max);

        result = distribute(re);

        return result;
    }

    long randomNumber(const long min, const long max)
    {
        long result;

        std::random_device rd;
        std::mt19937_64 re(rd());

        std::uniform_int_distribution<long> distr(min, max);

        result = distr(re);

        return result;
    }

    long long randomNumber(const long long min, const long long max)
    {
        long long result;

        std::random_device rd;
        std::mt19937_64 re(rd());

        std::uniform_int_distribution<long long> distr(min, max);

        result = distr(re);

        return result;
    }

    float randomNumber(const float min, const float max)
    {
        float result = 0.0f;

        std::random_device rd;
        std::default_random_engine re(rd());

        std::uniform_real_distribution<float> distribute(min, max);

        result = distribute(re);

        return result;
    }

    double randomNumber(const double min, const double max)
    {
        double result = 0.0;

        std::random_device rd;
        std::mt19937_64 re(rd());

        std::uniform_real_distribution<double> distr(min, max);

        result = distr(re);

        return result;
    }

    std::array<uint8_t, 16> randomBytes()
    {
        std::array<uint8_t, 16> bytes;

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> dis(0, 255);

        for (auto& byte : bytes)
        {
            byte = static_cast<uint8_t>(dis(gen));
        }

        return bytes;
    }

    std::string uuidV1()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

        // byte sequence
        std::array<uint8_t, 16> uuid_bytes = randomBytes();
        
        // timestamp
        uuid_bytes[0] = (timestamp >> 40) & 0xFF;
        uuid_bytes[1] = (timestamp >> 32) & 0xFF;
        uuid_bytes[2] = (timestamp >> 24) & 0xFF;
        uuid_bytes[3] = (timestamp >> 16) & 0xFF;
        uuid_bytes[4] = (timestamp >> 8) & 0xFF;
        uuid_bytes[5] = timestamp & 0xFF;

        // version 1
        uuid_bytes[6] = (uuid_bytes[6] & 0x0F) | 0x10;

        // variant to 10xx
        uuid_bytes[8] = (uuid_bytes[8] & 0x3F) | 0x80;

        std::ostringstream oss;
        oss << std::hex << std::setfill('0');

        for (size_t i = 0; i < uuid_bytes.size(); ++i)
        {
            if (i == 4 || i == 6 || i == 8 || i == 10)
            {
                oss << '-';
            }
            oss << std::setw(2) << static_cast<int>(uuid_bytes[i]);
        }

        return oss.str();
    }

    std::string uuidV4()
    {
        auto random_bytes = randomBytes();

        // version 4
        random_bytes[6] = (random_bytes[6] & 0x0F) | 0x40;

        // variant 10xx (RFC4122)
        random_bytes[8] = (random_bytes[8] & 0x3F) | 0x80;

        std::ostringstream oss;
        oss << std::hex << std::setfill('0');

        for (size_t i = 0; i < random_bytes.size(); ++i)
        {
            if (i == 4 || i == 6 || i == 8 || i == 10)
            {
                oss << '-';
            }
            oss << std::setw(2) << static_cast<int>(random_bytes[i]);
        }

        return oss.str();
    }

    std::string randomAlphanumeric(int length)
    {
        std::string result;

        if (length <= 0) { length = 1; }

        result.reserve(length);

        for (int i = 0; i < length; i++)
        {
            int j = randomNumber(0, (int)STRINGS_INTERNAL::alphanumeric.length() - 1);
            result += STRINGS_INTERNAL::alphanumeric[j];
        }

        return result;
    }

    std::string randomAlphanumericWithSpecialCharacter(int length)
    {
        std::string result;

        if (length <= 0) { length = 1; }

        result.reserve(length);

        for (int i = 0; i < length; i++)
        {
            int j = randomNumber(0, (int)STRINGS_INTERNAL::alphanumeric_with_special_character.length() - 1);
            result += STRINGS_INTERNAL::alphanumeric_with_special_character[j];
        }

        return result;
    }
} // namespace generate


namespace change
{
    std::string inputLetterCase(const std::string input, const int letterCase)
    {
        std::string result;

        result.reserve(input.length());

        switch (letterCase)
        {
            case 0:
            {
                for (size_t i = 0; i < input.length(); i++)
                {
                    result += tolower(input[i]);
                }
            }
            break;

            case 1:
            {
                for (size_t i = 0; i < input.length(); i++)
                {
                    result += toupper(input[i]);
                }
            }
            break;

            case 2:
            {
                for (size_t i = 0; i < input.length(); i++)
                {
                    //  0 is lower, 1 is upper
                    int mixedcase = generate::randomNumber(0, 1);

                    if (mixedcase == 0 && isalpha(input[i]))
                    {
                        result += tolower(input[i]);
                    }
                    else if (mixedcase == 1 && isalpha(input[i]))
                    {
                        result += toupper(input[i]);
                    }
                    else
                    {
                        result += input[i];
                    }
                }
            }
            break;

            default:
            {
                result = input;
            }
            break;
        }

        return result;
    }
} // namespace change


namespace string
{
    TBuffer toBuffer(const std::string &input, size_t requiredSize)
    {
        TBuffer result(input.begin(), input.end());

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
} // namespace string


#if LIBPRCPP_PROJECT_USING_JSONCPP
namespace json
{
    std::string toString(const Json::Value &input, const int &indent, const int &precision)
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

    Json::Value fromCSV(const std::string &csvFilePath)
    {
        Json::Value result;

        if (!find::inputEndsWith(csvFilePath, ".csv"))
        {
            std::cerr << "csvFilePath is not end with .csv\n";
            return result;
        }

        try
        {
            std::ifstream f(csvFilePath);
            std::string line;
            std::vector<std::string> headers;

            if (f.is_open())
            {
                if (std::getline(f, line))
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

                while (std::getline(f, line))
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
                            if (isNumeric(cell))
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

                f.close();
            }
            else
            {
                std::cerr << "json::fromCSV: can't find csv file from \"" << csvFilePath << "\"\n";
                result = Json::Value();
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "json::fromCSV: " << e.what() << '\n';
            result = Json::Value();
        }

        return result;
    }

    Json::Value fromFile(const std::string &filePath)
    {
        Json::Value result;

        std::ifstream f(filePath);

        if (f.is_open())
        {
            f >> result;
            f.close();
        }
        else
        {
            std::cerr << "json::fromFile: can't find json file from \"" << filePath << "\"\n";
        }

        return result;
    }

    Json::Value fromString(const std::string &jsonStringInput, const int &indent, const int &precision)
    {
        Json::Value result;

        try
        {
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

            JSONCPP_STRING err;
            Json::CharReaderBuilder builder;

            builder.settings_["indentation"] = _indentString;
            builder.settings_["precision"] = _precision;

            const int inputLength = static_cast<int>(jsonStringInput.length());

            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            reader->parse(jsonStringInput.c_str(), jsonStringInput.c_str() + inputLength, &result, &err);
        }
        catch(const std::exception& e)
        {
            std::cerr << "exception json::fromString: " << e.what() << '\n';
        }

        return result;
    }

    EResult saveToCSV(const std::string &jsonFilePath, const std::string &output)
    {
        EResult result = EResult::RESULT_UNDEFINED;

        std::ifstream f(jsonFilePath);
        if (!f.is_open())
        {
            std::cerr << "ERROR: can't open JSON file \"" << jsonFilePath << "\"\n";
            result = EResult::RESULT_ERROR;
            return result;
        }

        Json::CharReaderBuilder readerBuilder;
        Json::Value jsonData;
        std::string errs;

        if (!Json::parseFromStream(readerBuilder, f, &jsonData, &errs))
        {
            std::cerr << "ERROR: failed to parse json: \"" << errs << "\"\n";
            result = EResult::RESULT_ERROR;
            return result;
        }
        f.close();

        // open CSV file for writing
        std::ofstream csvFile(output);
        if (!csvFile.is_open())
        {
            std::cerr << "ERROR: can't open CSV file " << output << "\n";
            result = EResult::RESULT_ERROR;
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

            result = EResult::RESULT_OK;
        }
        else
        {
            std::cerr << "ERROR: json data is not an array or is empty" << "\n";
            result = EResult::RESULT_ERROR;
        }
        csvFile.close();

        return result;
    }

    EResult saveToJSON(const Json::Value &input, const std::string &output, const int &indent, const int &precision)
    {
        EResult result = EResult::RESULT_UNDEFINED;

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

            result = EResult::RESULT_OK;
        }
        else
        {
            std::cerr << "ERROR: can't save file to \"" << output << "\"\n";
            result = EResult::RESULT_ERROR;
        }

        return result;
    }
} // namespace json
#endif // LIBPRCPP_PROJECT_USING_JSONCPP


namespace read
{
    TBuffer fileAsBuffer(const std::string &filePath)
    {
        // // v0
        // std::ifstream file(filePath, std::ios::binary | std::ios::ate);

        // if (!file)
        // {
        //     std::cerr << "fileAsBuffer: can't opening file for writing\n";
        //     return {};
        // }

        // std::streamsize size = file.tellg();

        // if (size > std::numeric_limits<TBuffer::size_type>::max()) {
        //     std::cerr << "fileAsBuffer: file too large to process\n";
        //     return {};
        // }

        // file.seekg(0, std::ios::beg);
        // TBuffer buffer(size);

        // if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        // {
        //     std::cerr << "fileAsBuffer: can't writing to file\n";
        //     return {};
        // }

        // return buffer;

        // v1
        const size_t chunkSize = 1024 * 1024; // 1 MB
        TBuffer buffer(chunkSize);
        std::ifstream file(filePath, std::ios::binary);

        if (!file)
        {
            std::cerr << "fileAsBuffer: can't open file for reading\n";
            return {};
        }

        TBuffer result;

        while (file)
        {
            file.read(reinterpret_cast<char*>(buffer.data()), chunkSize);
            size_t bytesRead = file.gcount();

            if (bytesRead > 0)
            {
                // append the chunk to the result buffer
                result.insert(result.end(), buffer.begin(), buffer.begin() + bytesRead);
            }
        }

        return result;
    }

    bool fileExists(const std::string &path)
    {
        std::ifstream file(path);
        return file.good();
    }
} // namespace read


namespace write
{
    bool fileFromBuffer(const std::string &filePath, const TBuffer &bufferData)
    {
        std::ofstream file(filePath, std::ios::binary);

        if (!file)
        {
            std::cerr << "fileFromBuffer: opening file for writing\n";
            return false;
        }

        if (!file.write(reinterpret_cast<const char*>(bufferData.data()), bufferData.size()))
        {
            std::cerr << "fileFromBuffer: writing to file\n";
            return false;
        }

        return true;
    }
} // namespace write


} // namespace utilityFunctions
} // namespace libprcpp

#if LIBPRCPP_COMPILER_MSVC
#pragma warning (pop)
#endif // LIBPRCPP_COMPILER_MSVC
