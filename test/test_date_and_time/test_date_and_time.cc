#include <libprcpp/modules/date_and_time_module.hh>

using namespace libprcpp;

int main()
{
    std::cout << "TEST DATE & TIME\n";
    
    const int SELECTED_TIMEZONE = 7;
    const std::string SELECTED_DATE_AND_TIME = "2020-10-05T23:59:59";

    auto utcTimezone = dateAndTimeFunctions::UTC::timezone::toString();
    auto utcTimezoneOffset = dateAndTimeFunctions::UTC::timezone::toStringOffset(SELECTED_TIMEZONE);
    std::cout << "utcTimezone:\n    " << utcTimezone << "\n";
    std::cout << "utcTimezoneOffset:\n    " << utcTimezoneOffset << "\n";

    auto utcYearInt = dateAndTimeFunctions::UTC::year::toInt(SELECTED_TIMEZONE);
    auto utcYearString = dateAndTimeFunctions::UTC::year::toString(SELECTED_TIMEZONE);
    std::cout << "utcYearInt:\n    " << utcYearInt << "\n";
    std::cout << "utcYearString:\n    " << utcYearString << "\n";

    auto utcMonthInt = dateAndTimeFunctions::UTC::month::toInt(SELECTED_TIMEZONE);
    auto utcMonthString = dateAndTimeFunctions::UTC::month::toString(SELECTED_TIMEZONE);
    auto utcMonthStringHuman = dateAndTimeFunctions::UTC::month::toStringHuman(ELanguage::Enum::LANGUAGE_ENGLISH, SELECTED_TIMEZONE);
    std::cout << "utcMonthInt:\n    " << utcMonthInt << "\n";
    std::cout << "utcMonthString:\n    " << utcMonthString << "\n";
    std::cout << "utcMonthStringHuman:\n    " << utcMonthStringHuman << "\n";

    auto utcDayInt = dateAndTimeFunctions::UTC::day::toInt(SELECTED_TIMEZONE);
    auto utcDayString = dateAndTimeFunctions::UTC::day::toString(SELECTED_TIMEZONE);
    std::cout << "utcDayInt:\n    " << utcDayInt << "\n";
    std::cout << "utcDayString:\n    " << utcDayString << "\n";

    auto utcHourInt = dateAndTimeFunctions::UTC::hour::toInt(SELECTED_TIMEZONE);
    auto utcHourString = dateAndTimeFunctions::UTC::hour::toString(SELECTED_TIMEZONE);
    std::cout << "utcHourInt:\n    " << utcHourInt << "\n";
    std::cout << "utcHourString:\n    " << utcHourString << "\n";

    auto utcMinuteInt = dateAndTimeFunctions::UTC::minute::toInt(SELECTED_TIMEZONE);
    auto utcMinuteString = dateAndTimeFunctions::UTC::minute::toString(SELECTED_TIMEZONE);
    std::cout << "utcMinuteInt:\n    " << utcMinuteInt << "\n";
    std::cout << "utcMinuteString:\n    " << utcMinuteString << "\n";

    auto utcSecondInt = dateAndTimeFunctions::UTC::second::toInt(SELECTED_TIMEZONE);
    auto utcSecondString = dateAndTimeFunctions::UTC::second::toString(SELECTED_TIMEZONE);
    std::cout << "utcSecondInt:\n    " << utcSecondInt << "\n";
    std::cout << "utcSecondString:\n    " << utcSecondString << "\n";

    auto YYYYMMDD_int = dateAndTimeFunctions::UTC::YYYYMMDD::toInt(SELECTED_TIMEZONE);
    auto YYYYMMDD_string = dateAndTimeFunctions::UTC::YYYYMMDD::toString(SELECTED_TIMEZONE);
    auto YYYYMMDD_string_ISO8601 = dateAndTimeFunctions::UTC::YYYYMMDD::toStringISO8601(SELECTED_TIMEZONE);
    std::cout << "YYYYMMDD_int:\n    " << YYYYMMDD_int << "\n";
    std::cout << "YYYYMMDD_string:\n    " << YYYYMMDD_string << "\n";
    std::cout << "YYYYMMDD_string_ISO8601:\n    " << YYYYMMDD_string_ISO8601 << "\n";

    auto hhmmss_int = dateAndTimeFunctions::UTC::hhmmss::toInt(SELECTED_TIMEZONE);
    auto hhmmss_string = dateAndTimeFunctions::UTC::hhmmss::toString(SELECTED_TIMEZONE);
    auto hhmmss_stringHuman = dateAndTimeFunctions::UTC::hhmmss::toStringHuman(SELECTED_TIMEZONE);
    std::cout << "hhmmss_int:\n    " << hhmmss_int << "\n";
    std::cout << "hhmmss_string:\n    " << hhmmss_string << "\n";
    std::cout << "hhmmss_stringHuman:\n    " << hhmmss_stringHuman << "\n";

    auto YYYYMMDDhhmmss_int64 = dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toInt64(SELECTED_TIMEZONE);
    auto YYYYMMDDhhmmss_string = dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toString(SELECTED_TIMEZONE);
    auto YYYYMMDDhhmmss_millis = dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toMillis(SELECTED_DATE_AND_TIME);
    auto YYYYMMDDhhmmss_millisNow = dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toMillisNow(SELECTED_TIMEZONE);
    auto YYYYMMDDhhmmss_stringHuman = dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toStringHuman(SELECTED_TIMEZONE);
    std::cout << "YYYYMMDDhhmmss_int64:\n    " << YYYYMMDDhhmmss_int64 << "\n";
    std::cout << "YYYYMMDDhhmmss_string:\n    " << YYYYMMDDhhmmss_string << "\n";
    std::cout << "YYYYMMDDhhmmss_millis:\n    " << YYYYMMDDhhmmss_millis << "\n";
    std::cout << "YYYYMMDDhhmmss_millisNow:\n    " << YYYYMMDDhhmmss_millisNow << "\n";
    std::cout << "YYYYMMDDhhmmss_stringHuman:\n    " << YYYYMMDDhhmmss_stringHuman << "\n";

    auto YYYYMMDDhhmmssms_int64 = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toInt64(SELECTED_TIMEZONE);
    auto YYYYMMDDhhmmssms_string = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toString(SELECTED_TIMEZONE);
    auto YYYYMMDDhhmmssms_millis = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toMillis(std::string(SELECTED_DATE_AND_TIME+".123"));
    auto YYYYMMDDhhmmssms_millisNow = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toMillisNow(SELECTED_TIMEZONE);
    auto YYYYMMDDhhmmssms_stringHuman = dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toStringHuman(SELECTED_TIMEZONE);
    std::cout << "YYYYMMDDhhmmssms_int64:\n    " << YYYYMMDDhhmmssms_int64 << "\n";
    std::cout << "YYYYMMDDhhmmssms_string:\n    " << YYYYMMDDhhmmssms_string << "\n";
    std::cout << "YYYYMMDDhhmmssms_millis:\n    " << YYYYMMDDhhmmssms_millis << "\n";
    std::cout << "YYYYMMDDhhmmssms_millisNow:\n    " << YYYYMMDDhhmmssms_millisNow << "\n";
    std::cout << "YYYYMMDDhhmmssms_stringHuman:\n    " << YYYYMMDDhhmmssms_stringHuman << "\n";

    return 0;
}
