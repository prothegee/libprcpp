#include "utility_module.hh"

#include <regex>
#include <iostream>
#include <fstream>

#if LIBPRCPP_BUILD_COMPILER_ID == 1
// RESERVED
#elif LIBPRCPP_BUILD_COMPILER_ID == 2
#pragma warning (push)
#pragma warning (disable : 4996)
#pragma warning (disable : 4242)
#pragma warning (disable : 4244)
#elif LIBPRCPP_BUILD_COMPILER_ID == 3
// RESERVED
#endif

namespace libprcpp
{

CUtilityModule::CUtilityModule()
{
}

CUtilityModule::~CUtilityModule()
{
}

std::string CUtilityModule::base64encode(const std::string &input)
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

std::string CUtilityModule::base64decode(const std::string &input)
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

void CUtilityModule::SFind::andReplaceAll(std::string &source, const std::string &query, const std::string &replacement)
{
    size_t position = 0;

    while ((position = source.find(query, position)) != std::string::npos)
    {
        source.replace(position, query.size(), replacement);
        position += replacement.size();
    }
}

int CUtilityModule::SFind::eachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords)
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

bool CUtilityModule::SFind::keywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction)
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

bool CUtilityModule::SFind::keywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction)
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

int CUtilityModule::SGenerate::randomNumber(const int min, const int max)
{
    int result;

    std::random_device rd;
    std::default_random_engine re(rd());

    std::uniform_int_distribution<int> distribute(min, max);

    result = distribute(re);

    return result;
}

long CUtilityModule::SGenerate::randomNumber(const long min, const long max)
{
    long result;

    std::random_device rd;
    std::mt19937_64 re(rd());

    std::uniform_int_distribution<long> distr(min, max);

    result = distr(re);

    return result;
}

long long CUtilityModule::SGenerate::randomNumber(const long long min, const long long max)
{
    long long result;

    std::random_device rd;
    std::mt19937_64 re(rd());

    std::uniform_int_distribution<long long> distr(min, max);

    result = distr(re);

    return result;
}

float CUtilityModule::SGenerate::randomNumber(const float min, const float max)
{
    float result = 0.0f;

    std::random_device rd;
    std::default_random_engine re(rd());

    std::uniform_real_distribution<float> distribute(min, max);

    result = distribute(re);

    return result;
}

double CUtilityModule::SGenerate::randomNumber(const double min, const double max)
{
    double result = 0.0;

    std::random_device rd;
    std::mt19937_64 re(rd());

    std::uniform_real_distribution<double> distr(min, max);

    result = distr(re);

    return result;
}

std::array<uint8_t, 16> CUtilityModule::SGenerate::randomBytes()
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

std::string CUtilityModule::SGenerate::uuidV1()
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

std::string CUtilityModule::SGenerate::uuidV4()
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

std::string CUtilityModule::SGenerate::randomAlphanumeric(int length)
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

std::string CUtilityModule::SGenerate::randomAlphanumericWithSpecialCharacter(int length)
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

std::string CUtilityModule::SChange::inputLetterCase(const std::string input, const int letterCase)
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
            SGenerate gen = SGenerate();

            for (size_t i = 0; i < input.length(); i++)
            {
                //  0 is lower, 1 is upper
                int mixedcase = gen.randomNumber(0, 1);

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

Json::Value CUtilityModule::SJson::fromFile(const std::string &filePath)
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
        std::cerr << "ERROR FileJSON: can't find json file from \"" << filePath << "\" in \"CUtilityModule::SJson::fromFile\"\n";
    }

    return result;
}

Json::Value CUtilityModule::SJson::fromString(const std::string &jsonStringInput, const int &indent, const int &precision)
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
        std::cerr << "EXCEPTION utilityFunctions::json::fromString: " << e.what() << '\n';
    }

    return result;
}

namespace utilityFunctions
{
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

    namespace find
    {
        void andReplaceAll(std::string &source, const std::string &query, const std::string &replacement)
        {
            CUtilityModule UTILITY;
            UTILITY.Find.andReplaceAll(source, query, replacement);
        }

        int eachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords)
        {
            CUtilityModule UTILITY;
            return UTILITY.Find.eachKeywords(source, keywords, foundKeywords);
        }

        bool keywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction)
        {
            CUtilityModule UTILITY;
            return UTILITY.Find.keywordBefore(source, keywordBefore, extraction);
        }

        bool keywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction)
        {
            CUtilityModule UTILITY;
            return UTILITY.Find.keywordAfter(source, keywordAfter, extraction);
        }
    } // namespace find

    namespace generate
    {
        int randomNumber(const int min, const int max)
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomNumber(min, max);
        }

        long randomNumber(const long min, const long max)
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomNumber(min, max);
        }

        long long randomNumber(const long long min, const long long max)
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomNumber(min, max);
        }

        float randomNumber(const float min, const float max)
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomNumber(min, max);
        }

        double randomNumber(const double min, const double max)
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomNumber(min, max);
        }

        std::array<uint8_t, 16> randomBytes()
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomBytes();
        }

        std::string uuidV1()
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.uuidV1();
        }

        std::string uuidV4()
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.uuidV4();
        }

        std::string randomAlphanumeric(int length)
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomAlphanumeric(length);
        }

        std::string randomAlphanumericWithSpecialCharacter(int length)
        {
            CUtilityModule UTILITY;
            return UTILITY.Generate.randomAlphanumericWithSpecialCharacter(length);
        }
    } // namespace generate

    namespace change
    {
        std::string inputLetterCase(const std::string input, const int letterCase)
        {
            CUtilityModule UTILITY;
            return UTILITY.Change.inputLetterCase(input, letterCase);
        }
    } // namespace change

    namespace json
    {
        Json::Value fromFile(const std::string &filePath)
        {
            CUtilityModule UTILITY;
            return UTILITY.JSON.fromFile(filePath);
        }

        Json::Value fromString(const std::string &jsonStringInput, const int &indent, const int &precision)
        {
            CUtilityModule UTILITY;
            return UTILITY.JSON.fromString(jsonStringInput, indent, precision);
        }
    } // namespace json
} // namespace utilityFunctions

} // namespace libprcpp

#if LIBPRCPP_BUILD_COMPILER_ID == 1
// RESERVED
#elif LIBPRCPP_BUILD_COMPILER_ID == 2
#pragma warning (pop)
#elif LIBPRCPP_BUILD_COMPILER_ID == 3
// RESERVED
#endif
