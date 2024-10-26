#include "date_and_time_module.hh"

namespace libprcpp
{

CDateAndTime::CDateAndTime()
{
}

CDateAndTime::~CDateAndTime()
{
}

std::string CDateAndTime::SUTC::STimeZone::toString()
{
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    ss << std::put_time(std::gmtime(&now_time), "%Y-%m-%dT%H:%M:%S+00:00");
    result = ss.str();

    return result;
}

std::string CDateAndTime::SUTC::STimeZone::toStringOffset(const int &timeOffset, const bool &ISO8601)
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

int CDateAndTime::SUTC::SYear::toInt(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SYear::toString(const int &timeOffset)
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

int CDateAndTime::SUTC::SMonth::toInt(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SMonth::toString(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SMonth::toStringHuman(const ELanguage::Enum &languageEnum, const int &timeOffset)
{
    std::string result, tmpStr1;
            
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%m");

    tmpStr1 = ss.str();

    if (tmpStr1.rfind("0", 0) == 0)
    {
        tmpStr1.replace(0, 1, "");
    }

    const auto MONTH = std::stoi(tmpStr1);
    
    result = "";

    // IMPORTANT: CHECK MULTIPLE LANGUAGES
    switch (languageEnum)
    {
        case ELanguage::Enum::LANGUAGE_ENGLISH:
        {
            if (MONTH ==  1) { result = "Jan"; } 
            if (MONTH ==  2) { result = "Feb"; } 
            if (MONTH ==  3) { result = "Mar"; } 
            if (MONTH ==  4) { result = "Apr"; } 
            if (MONTH ==  5) { result = "May"; } 
            if (MONTH ==  6) { result = "Jun"; } 
            if (MONTH ==  7) { result = "Jul"; } 
            if (MONTH ==  8) { result = "Aug"; } 
            if (MONTH ==  9) { result = "Sep"; } 
            if (MONTH == 10) { result = "Oct"; } 
            if (MONTH == 11) { result = "Nov"; } 
            if (MONTH == 12) { result = "Dec"; } 
        }
        break;

        default:
        {
            if (MONTH ==  1) { result = "Jan"; } 
            if (MONTH ==  2) { result = "Feb"; } 
            if (MONTH ==  3) { result = "Mar"; } 
            if (MONTH ==  4) { result = "Apr"; } 
            if (MONTH ==  5) { result = "May"; } 
            if (MONTH ==  6) { result = "Jun"; } 
            if (MONTH ==  7) { result = "Jul"; } 
            if (MONTH ==  8) { result = "Aug"; } 
            if (MONTH ==  9) { result = "Sep"; } 
            if (MONTH == 10) { result = "Oct"; } 
            if (MONTH == 11) { result = "Nov"; } 
            if (MONTH == 12) { result = "Dec"; } 
        }
        break;
    }

    return result;
}

int CDateAndTime::SUTC::SDay::toInt(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SDay::toString(const int &timeOffset)
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

int CDateAndTime::SUTC::SHour::toInt(const int & timeOffset)
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

std::string CDateAndTime::SUTC::SHour::toString(const int &timeOffset)
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

int CDateAndTime::SUTC::SMinute::toInt(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SMinute::toString(const int &timeOffset)
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

int CDateAndTime::SUTC::SSecond::toInt(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SSecond::toString(const int &timeOffset)
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

int CDateAndTime::SUTC::SYYYYMMDD::toInt(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SYYYYMMDD::toString(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SYYYYMMDD::toStringISO8601(const int &timeOffset)
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

int CDateAndTime::SUTC::SHhMmSs::toInt(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SHhMmSs::toString(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SHhMmSs::toStringHuman(const int &timeOffset)
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

    ss << std::put_time(std::gmtime(&now_time_utc), "%H:%M:%S");

    result = ss.str();

    return result;
}

int64_t CDateAndTime::SUTC::SYYYYMMDDhhmmss::toInt64(const int &timeOffset)
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

int64_t CDateAndTime::SUTC::SYYYYMMDDhhmmss::toMillis(const std::string &YYYYMMDDhhmmss)
{
    int64_t result;

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

int64_t CDateAndTime::SUTC::SYYYYMMDDhhmmss::toMillisNow(const int &timeOffset)
{
    int64_t result;

    std::string tmpStr;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%dT%H:%M:%S");

    tmpStr = ss.str();

    std::tm time = {};
    std::stringstream sss(tmpStr);

    sss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();

    return result;
}

std::string CDateAndTime::SUTC::SYYYYMMDDhhmmss::toString(const int &timeOffset)
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

std::string CDateAndTime::SUTC::SYYYYMMDDhhmmss::toStringHuman(const int &timeOffset, const bool &useTimeSign)
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
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%dT%H:%M:%S");
    }
    else
    {
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%d %H:%M:%S");
    }

    result = ss.str();

    return result;
}

std::string CDateAndTime::SUTC::SYYYYMMDDhhmmss::toStringSecondsOffset(const int &secondsOffset)
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

int64_t CDateAndTime::SUTC::SYYYYMMDDhhmmssms::toMillis(const std::string &YYYYMMDDhhmmssms)
{
    int64_t result;

    std::tm time = {};
    std::istringstream ss(YYYYMMDDhhmmssms);

    if (YYYYMMDDhhmmssms.find("T") != std::string::npos)
    {
        ss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
    }
    else
    {
        ss >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    }

    if (ss.fail())
    {
        throw std::runtime_error("ERROR YYYYMMDDhhmmssms: Failed to parse time string");
    }

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();

    return result;
}

int64_t CDateAndTime::SUTC::SYYYYMMDDhhmmssms::toMillisNow(const int &timeOffset)
{
    int64_t result;

    std::string tmpStr;
    std::stringstream ss;
    int timezoneOffset = timeOffset;

    if (timezoneOffset <= -11) { timezoneOffset = -11; }
    if (timezoneOffset >= 14) { timezoneOffset = 14; }

    auto adjustTimeOffset = timezoneOffset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%dT%H%M%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();

    tmpStr = ss.str();

    std::tm time = {};
    std::stringstream sss(tmpStr);

    sss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");

    int millis = 0;
    if (sss.peek() == '.')
    {
        sss.ignore();
        sss >> millis;
    }

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();
    result += millis;

    return result;
}

std::string CDateAndTime::SUTC::SYYYYMMDDhhmmssms::toString(const int &timeOffset)
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

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(std::gmtime(&now_time_utc), "%Y%m%d%H%M%S") << std::setw(3) << std::setfill('0') << milliseconds.count();

    result = ss.str();

    return result;
}

std::string CDateAndTime::SUTC::SYYYYMMDDhhmmssms::toStringHuman(const int &timeOffset, const bool &useTimeSign)
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

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    if (useTimeSign)
    {
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%dT%H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
    }
    else
    {
        ss << std::put_time(std::gmtime(&now_time_utc), "%Y-%m-%d %H%:M:%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
    }

    result = ss.str();

    return result;
}

std::string CDateAndTime::SUTC::SYYYYMMDDhhmmssms::toStringSecondOffset(const int &secondsOffset)
{
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::seconds(secondsOffset);

    auto future_time = now + seconds;

    std::time_t future_time_t = std::chrono::system_clock::to_time_t(future_time);

    std::tm future_tm = *std::gmtime(&future_time_t);

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&future_tm, "%Y%m%d%H%M%S") << std::setw(3) << std::setfill('0') << milliseconds.count();

    result = ss.str();

    return result;
}

namespace dateAndTimeFunctions
{
    namespace UTC
    {
        namespace timezone
        {
            std::string toString()
            {
                CDateAndTime DT;
                return DT.UTC.TimeZone.toString();
            }

            std::string toStringOffset(const int &timeOffset, const bool &ISO8601)
            {
                CDateAndTime DT;
                return DT.UTC.TimeZone.toStringOffset(timeOffset, ISO8601);
            }
        } // namespace timeZone

        namespace year
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Year.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Year.toString(timeOffset);
            }
        } // namespace year

        namespace month
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Month.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Month.toString(timeOffset);
            }

            std::string toStringHuman(const ELanguage::Enum &languageEnum, const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Month.toStringHuman(languageEnum, timeOffset);
            }
        } // namespace month

        namespace day
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Day.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Day.toString(timeOffset);
            }
        } // namespace day

        namespace hour
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Hour.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Hour.toString(timeOffset);
            }
        } // namespace hour

        namespace minute
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Minute.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Minute.toString(timeOffset);
            }
        } // namespace minute

        namespace second
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Second.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.Second.toString(timeOffset);
            }
        } // namespace second

        namespace YYYYMMDD
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDD.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDD.toString(timeOffset);
            }

            std::string toStringISO8601(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDD.toStringISO8601(timeOffset);
            }
        } // namespace YYYYMMDD

        namespace hhmmss
        {
            int toInt(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.hhmmss.toInt(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.hhmmss.toString(timeOffset);
            }

            std::string toStringHuman(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.hhmmss.toStringHuman(timeOffset);
            }
        } // namespace hhmmss

        namespace YYYYMMDDhhmmss
        {
            int64_t toInt64(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmss.toInt64(timeOffset);
            }

            int64_t toMillis(const std::string &YYYYMMDDhhmmss)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmss.toMillis(YYYYMMDDhhmmss);
            }

            int64_t toMillisNow(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmss.toMillisNow(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmss.toString(timeOffset);
            }

            std::string toStringHuman(const int &timeOffset, const bool &useTimeSign)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmss.toStringHuman(timeOffset, useTimeSign);
            }

            std::string toStringSecondsOffset(const int &secondsOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmss.toStringSecondsOffset(secondsOffset);
            }
        } // namespace YYYYMMDDhhmmss

        namespace YYYYMMDDhhmmssms
        {
            int64_t toMillis(const std::string &YYYYMMDDhhmmssms)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmssms.toMillis(YYYYMMDDhhmmssms);
            }

            int64_t toMillisNow(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmssms.toMillisNow(timeOffset);
            }

            std::string toString(const int &timeOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmssms.toString(timeOffset);
            }

            std::string toStringHuman(const int &timeOffset, const bool &useTimeSign)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmssms.toStringHuman(timeOffset, useTimeSign);
            }

            std::string toStringSecondOffset(const int &secondsOffset)
            {
                CDateAndTime DT;
                return DT.UTC.YYYYMMDDhhmmssms.toStringSecondOffset(secondsOffset);
            }
        } // namespace YYYYMMDDhhmmssms
    } // namespace UTC
} // namespace dateAndTimeFunctions

} // namespace libprcpp
