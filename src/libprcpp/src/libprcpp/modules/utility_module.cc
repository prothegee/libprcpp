#include "utility_module.h"

#include <regex>
#include <iostream>
#include <fstream>

#if PROJECT_BUILD_COMPILER_ID == 1
// RESERVED
#elif PROJECT_BUILD_COMPILER_ID == 2
#pragma warning (push)
#pragma warning (disable : 4996)
#pragma warning (disable : 4242)
#pragma warning (disable : 4244)
#elif PROJECT_BUILD_COMPILER_ID == 3
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

void CUtilityModule::findAndReplaceAll(std::string &source, const std::string &query, const std::string &replacement)
{
    size_t position = 0;

    while ((position = source.find(query, position)) != std::string::npos)
    {
        source.replace(position, query.size(), replacement);
        position += replacement.size();
    }
}

int CUtilityModule::findEachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords)
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

bool CUtilityModule::findKeywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction)
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

bool CUtilityModule::findKeywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction)
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

int CUtilityModule::generateRandomNumber(const int min, const int max)
{
    int result;

    std::random_device rd;
    std::default_random_engine re(rd());

    std::uniform_int_distribution<int> distribute(min, max);

    result = distribute(re);

    return result;
}

long CUtilityModule::generateRandomNumber(const long min, const long max)
{
    long result;

    std::random_device rd;
    std::mt19937_64 re(rd());

    std::uniform_int_distribution<long> distr(min, max);

    result = distr(re);

    return result;
}

long long CUtilityModule::generateRandomNumber(const long long min, const long long max)
{
    long long result;

    std::random_device rd;
    std::mt19937_64 re(rd());

    std::uniform_int_distribution<long long> distr(min, max);

    result = distr(re);

    return result;
}

float CUtilityModule::generateRandomNumber(const float min, const float max)
{
    float result = 0.0f;

    std::random_device rd;
    std::default_random_engine re(rd());

    std::uniform_real_distribution<float> distribute(min, max);

    result = distribute(re);

    return result;
}

double CUtilityModule::generateRandomNumber(const double min, const double max)
{
    double result = 0.0;

    std::random_device rd;
    std::mt19937_64 re(rd());

    std::uniform_real_distribution<double> distr(min, max);

    result = distr(re);

    return result;
}

std::array<uint8_t, 16> CUtilityModule::generateRandomBytes()
{
    std::array<uint8_t, 16> bytes;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int32_t> distribution(0, 255);

    for (auto &byte : bytes)
    {
        byte = distribution(generator);
    }

    return bytes;
}

std::string CUtilityModule::generateRandomAlphanumeric(int length)
{
    std::string result;

    if (length <= 0) { length = 1; }

    result.reserve(length);

    for (int i = 0; i < length; i++)
    {
        int j = generateRandomNumber(0, (int)m_alphanumeric.length() - 1);
        result += m_alphanumeric[j];
    }

    return result;
}

std::string CUtilityModule::generateRandomAlphanumericWithSpecialCharacter(int length)
{
    std::string result;

    if (length <= 0) { length = 1; }

    result.reserve(length);

    for (int i = 0; i < length; i++)
    {
        int j = generateRandomNumber(0, (int)m_alphanumericWithSpecialCharacter.length() - 1);
        result += m_alphanumericWithSpecialCharacter[j];
    }

    return result;
}

std::string CUtilityModule::changeInputLetterCase(const std::string input, const int letterCase)
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
                int mixedcase = generateRandomNumber(0, 1);

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

std::string CUtilityModule::generateUuidV1()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    // byte sequence
    std::array<uint8_t, 16> uuid_bytes = generateRandomBytes();
    
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

std::string CUtilityModule::generateUuidV4()
{
    auto random_bytes = generateRandomBytes();

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

bool CUtilityModule::checkInputIsAlphabetic(const std::string input) const
{
    auto itter = std::find_if(input.begin(), input.end(), [](char const& c)
    {
        return !isalpha(c);
    });

    return itter == input.end();
}

bool CUtilityModule::checkInputIsAlphaNumeric(const std::string input) const
{
    auto itter = std::find_if(input.begin(), input.end(), [](char const& c)
    {
        return !isalnum(c);
    });

    return itter == input.end();
}

bool CUtilityModule::checkInputPasswordMeetRequirement(const std::string &input, const ERequirementPasswordInput::Enum &requirement) const
{
    bool result = false;

    switch (requirement)
    {
        case ERequirementPasswordInput::Enum::REQUIREMENT_PASSWORD_INPUT_MIN_LENGTH_6:
        {
            if (input.length() >= 6) { result = true; }
        }
        break;

        case ERequirementPasswordInput::Enum::REQUIREMENT_PASSWORD_INPUT_MIN_LENGTH_6_WITH_1_NUMERIC_AND_1_SPECIAL_CHARACTER:
        {
            bool alphabetFound = false;
            bool numericFound = false;
            bool specialcharFound = false;

            if (input.length() >= 6)
            {
                for (size_t i = 0; i < m_alphabet.length(); i++)
                {
                    for (size_t j = 0; j < input.length(); j++)
                    {
                        if (m_alphabet[i] == input[j])
                        {
                            alphabetFound = true;
                            break;
                        }
                    }
                }

                for (size_t i = 0; i < m_numeric.length(); i++)
                {
                    for (size_t j = 0; j < input.length(); j++)
                    {
                        if (m_numeric[i] == input[j])
                        {
                            numericFound = true;
                            break;
                        }
                    }
                }

                for (size_t i = 0; i < m_specialCharacter.length(); i++)
                {
                    for (size_t j = 0; j < input.length(); j++)
                    {
                        if (m_specialCharacter[i] == input[j])
                        {
                            specialcharFound = true;
                            break;
                        }
                    }
                }

                if (alphabetFound && numericFound && specialcharFound)
                {
                    result = true;
                }
                else
                {
                    result = false;
                }
            }
        }
        break;

        default:
        {
            result = false;
        }
        break;
    }

    return result;
}

bool CUtilityModule::checkInputUsernameMeetRequirement(const std::string &input, const ERequirementUsernameInput::Enum &requirement) const
{
    bool result = false;

    switch (requirement)
    {
        case ERequirementUsernameInput::Enum::REQUIREMENT_USERNAME_INPUT_ALPHANUMERIC_UNDERSCORE:
        {
            std::regex invalidRegex(R"([^a-zA-Z0-9_])");

            result = !std::regex_search(input, invalidRegex);
        }
        break;

        default:
        {
            std::cerr << "ERROR: requirement param is undefined in \"CUtilityModule::checkInputUsernameMeetRequirement\"\n";            
        }
        break;
    }

    return result;
}

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string CUtilityModule::base64encode(const std::string &input)
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input.c_str(), input.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    std::string result(bufferPtr->data, bufferPtr->length);

    BIO_free_all(bio);

    return result;
}

std::string CUtilityModule::base64decode(const std::string &input)
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    bio = BIO_new_mem_buf(input.c_str(), -1);
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    char* output = new char[input.size()];

    int decodedLength = BIO_read(bio, output, input.size());

    BIO_free_all(bio);

    std::string result(output, decodedLength);

    delete[] output;

    return result;
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

std::string CUtilityModule::SDateAndTime::SUTC::STimeZone::toStringTZ()
{
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    ss << std::put_time(std::gmtime(&now_time), "%Y-%m-%dT%H:%M:%S+00:00");
    result = ss.str();

    return result;
}

std::string CUtilityModule::SDateAndTime::SUTC::STimeZone::toStringTZ(const int &timeOffset, const bool &ISO8601)
{
    std::string result;
    std::string utcNegativeOrPositive, utcFormat;
    std::stringstream ss;

    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    if (timezoneOffset <= -1) { utcNegativeOrPositive = ""; }
    if (timezoneOffset >= 0) { utcNegativeOrPositive = "+"; }

    if (timezoneOffset >= 0 && timezoneOffset <= 9)
    {
        utcFormat = "0" + std::to_string(timezoneOffset);
    }
    else if (timezoneOffset <= -1 && timezoneOffset >= -9)
    {
        utcFormat = std::to_string(timezoneOffset);
        utcFormat.insert(1, "0");
    }
    else
    {
        utcFormat = std::to_string(timezoneOffset);
    }

    utcFormat += ":00";

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    if (ISO8601)
    {
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%dT%H:%M:%S");
    }
    else
    {
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%d %H:%M:%S");
    }

    result = ss.str();

    if (ISO8601)
    {
        result += utcNegativeOrPositive;
        result += utcFormat;
    }
    else
    {
        result += " ";
        result += utcNegativeOrPositive;
        result += utcFormat;
    }

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCYear::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y");

    result = ss.str();

    return std::stoi(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCYear::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y");

    result = ss.str();

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCMonth::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%m");

    result = ss.str();

    if (result.rfind("0", 0) == 0)
    {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCMonth::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%m");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCDay::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%d");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCDay::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%d");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCHour::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%H");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCHour::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%H");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCMinute::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%M");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCMinute::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%M");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCSecond::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%S");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCSecond::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%S");

    result = ss.str();

    if (result.at(0) == '0')
    {
        result.replace(0, 1, "");
    }

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDay::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%d");

    result = ss.str();

    return std::stoi(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDay::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%d");

    result = ss.str();

    return result;
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDay::toStringISO8601(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%d");

    result = ss.str();

    return result;
}

int CUtilityModule::SDateAndTime::SUTC::SUTCHourMinuteSecond::toInt(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%H%M%S");

    result = ss.str();

    return std::stol(result);
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCHourMinuteSecond::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%H%M%S");

    result = ss.str();

    return result;
}

TInt64 CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDayHourMinuteSecond::toInt64(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%d%H%M%S");

    result = ss.str();

    return std::stol(result);
}

TInt64 CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDayHourMinuteSecond::toMillis(const std::string &YYYYMMDDhhmmss)
{
    TInt64 result;

    std::tm time = {};
    std::istringstream ss(YYYYMMDDhhmmss);

    if (YYYYMMDDhhmmss.find("T") != std::string::npos)
    {
        ss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
    }
    else
    {
        ss >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    }

    if (ss.fail())
    {
        throw std::runtime_error("ERROR YYYYMMDDhhmmss: Failed to parse time string");
    }

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();

    return result;
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDayHourMinuteSecond::toString(const int &timeOffset)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%d%H%M%S");

    result = ss.str();

    return result;
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDayHourMinuteSecond::toStringHuman(const int &timeOffset, const bool &useTimeSign)
{
    std::string result;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    if (useTimeSign)
    {
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%dT%H%M%S");
    }
    else
    {
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%d %H%M%S");
    }

    result = ss.str();

    return result;
}

std::string CUtilityModule::SDateAndTime::SUTC::SUTCYearMonthDayHourMinuteSecond::toStringSecondsOffset(const int &secondsOffset)
{
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::seconds(secondsOffset);

    auto future_time = now + seconds;

    std::time_t future_time_t = std::chrono::system_clock::to_time_t(future_time);

    std::tm future_tm = *std::gmtime(&future_time_t);

    ss << std::put_time(&future_tm, "%Y%m%d%H%M%S");

    result = ss.str();

    return result;
}

namespace utilityFunctions
{

void findAndReplaceAll(std::string &source, const std::string &query, const std::string &replacement)
{
    CUtilityModule Utility;
    Utility.findAndReplaceAll(source, query, replacement);
}

int findEachKeywords(const std::string &source, const std::vector<std::string> &keywords, std::vector<std::string> &foundKeywords)
{
    CUtilityModule Utility;
    return Utility.findEachKeywords(source, keywords, foundKeywords);
}

bool findKeywordBefore(const std::string &source, const std::string &keywordBefore, std::string &extraction)
{
    CUtilityModule Utility;
    return Utility.findKeywordBefore(source, keywordBefore, extraction);
}

bool findKeywordAfter(const std::string &source, const std::string &keywordAfter, std::string &extraction)
{
    CUtilityModule Utility;
    return Utility.findKeywordAfter(source, keywordAfter, extraction);
}

int generateRandomNumber(const int min, const int max)
{
    CUtilityModule Utility;
    return Utility.generateRandomNumber(min, max);
}

long generateRandomNumber(const long min, const long max)
{
    CUtilityModule Utility;
    return Utility.generateRandomNumber(min, max);
}

long long generateRandomNumber(const long long min, const long long max)
{
    CUtilityModule Utility;
    return Utility.generateRandomNumber(min, max);
}

float generateRandomNumber(const float min, const float max)
{
    CUtilityModule Utility;
    return Utility.generateRandomNumber(min, max);
}

double generateRandomNumber(const double min, const double max)
{
    CUtilityModule Utility;
    return Utility.generateRandomNumber(min, max);
}

std::array<uint8_t, 16> generateRandomBytes()
{
    CUtilityModule Utility;
    return Utility.generateRandomBytes();
}

std::string generateRandomAlphanumeric(int length)
{
    CUtilityModule Utility;
    return Utility.generateRandomAlphanumeric(length);
}

std::string generateRandomAlphanumericWithSpecialCharacter(int length)
{
    CUtilityModule Utility;
    return Utility.generateRandomAlphanumericWithSpecialCharacter(length);
}

std::string changeInputLetterCase(const std::string input, const int letterCase)
{
    CUtilityModule Utility;
    return Utility.changeInputLetterCase(input, letterCase);
}

std::string generateUuidV1()
{
    CUtilityModule Utility;
    return Utility.generateUuidV1();
}

std::string generateUuidV4()
{
    CUtilityModule Utility;
    return Utility.generateUuidV4();
}

bool checkInputIsAlphabetic(const std::string input)
{
    CUtilityModule Utility;
    return Utility.checkInputIsAlphabetic(input);
}

bool checkInputIsAlphaNumeric(const std::string input)
{
    CUtilityModule Utility;
    return Utility.checkInputIsAlphaNumeric(input);
}

bool checkInputPasswordMeetRequirement(const std::string &input, const ERequirementPasswordInput::Enum &requirement)
{
    CUtilityModule Utility;
    return Utility.checkInputPasswordMeetRequirement(input, requirement);
}

bool checkInputUsernameMeetRequirement(const std::string &input, const ERequirementUsernameInput::Enum &requirement)
{
    CUtilityModule Utility;
    return Utility.checkInputUsernameMeetRequirement(input, requirement);
}

#if LIBPRCPP_PROJECT_USING_OPENSSL
std::string base64encode(const std::string &input)
{
    CUtilityModule Utility;
    return Utility.base64encode(input);
}

std::string base64decode(const std::string &input)
{
    CUtilityModule Utility;
    return Utility.base64decode(input);
}
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

} // namespace utilityFunctions

namespace dateAndTime
{

namespace UTC
{

    namespace timeZone
    {
        std::string toString()
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.TimeZone.toStringTZ();
        }

        std::string toString(const int &timeOffset, const bool &ISO8601 = true)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.TimeZone.toStringTZ(timeOffset, ISO8601);
        }
    } // namespace timeZone

    namespace year
    {
        int toInt(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Year.toInt(timeOffset);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Year.toString(timeOffset);
        }
    } // namespace year

    namespace month
    {
        int toInt(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Month.toInt(timeOffset);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Month.toString(timeOffset);
        }
    } // namespace month

    namespace day
    {
        int toInt(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Day.toInt(timeOffset);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Day.toString(timeOffset);
        }
    } // namespace day

    namespace hour
    {
        int toInt(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Hour.toInt(timeOffset);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Hour.toString(timeOffset);
        }
    } // namespace hour

    namespace second
    {
        int toInt(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Second.toInt(timeOffset);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.Second.toString(timeOffset);
        }
    } // namespace second

    namespace YYYYMMDD
    {
        int toInt(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDD.toInt(timeOffset);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDD.toString(timeOffset);
        }

        std::string toStringISO8601(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDD.toStringISO8601(timeOffset);
        }
    } // namespace YYYYMMDD

    namespace hhmmss
    {
        int toInt(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.hhmmss.toInt(timeOffset);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.hhmmss.toString(timeOffset);
        }
    } // namespace hhmmss

    namespace YYYYMMDDhhmmss
    {
        TInt64 toInt64(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDDhhmmss.toInt64(timeOffset);
        }

        TInt64 toMillis(const std::string &YYYYMMDDhhmmss)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDDhhmmss.toMillis(YYYYMMDDhhmmss);
        }

        std::string toString(const int &timeOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDDhhmmss.toString(timeOffset);
        }

        std::string toStringHuman(const int &timeOffset, const bool &useTimeSign)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDDhhmmss.toStringHuman(timeOffset, useTimeSign);
        }

        std::string toStringSecondsOffset(const int &secondsOffset = 0)
        {
            CUtilityModule Utility;
            return Utility.DateAndTime.UTC.YYYYMMDDhhmmss.toStringSecondsOffset(secondsOffset);
        }
    } // namespace YYYYMMDDhhmmss

} // namespace UTC

} // namespace dateAndTime

} // namespace libprcpp

#if PROJECT_BUILD_COMPILER_ID == 1
// RESERVED
#elif PROJECT_BUILD_COMPILER_ID == 2
#pragma warning (pop)
#elif PROJECT_BUILD_COMPILER_ID == 3
// RESERVED
#endif
