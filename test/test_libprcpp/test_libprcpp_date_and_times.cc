#include <libprcpp/functions/date_and_time_funcs.hh>

using namespace libprcpp;

int main()
{
    std::printf("start test for test_date_and_times\n");

    std::printf("dateAndTimeFunctions::UTC::year::toString():                  %s\n", dateAndTimeFunctions::UTC::year::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::month::toString():                 %s\n", dateAndTimeFunctions::UTC::month::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::day::toString():                   %s\n", dateAndTimeFunctions::UTC::day::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::hour::toString():                  %s\n", dateAndTimeFunctions::UTC::hour::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::minute::toString():                %s\n", dateAndTimeFunctions::UTC::minute::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::second::toString():                %s\n", dateAndTimeFunctions::UTC::second::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::timeZone::toString():              %s\n", dateAndTimeFunctions::UTC::timeZone::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDD::toString():              %s\n", dateAndTimeFunctions::UTC::YYYYMMDD::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDD::toStringISO8601():       %s\n", dateAndTimeFunctions::UTC::YYYYMMDD::toStringISO8601().c_str());
    std::printf("dateAndTimeFunctions::UTC::hhmmss::toString():                %s\n", dateAndTimeFunctions::UTC::hhmmss::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::hhmmss::toStringHuman():           %s\n", dateAndTimeFunctions::UTC::hhmmss::toStringHuman().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toString():        %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toStringHuman():   %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmss::toStringHuman().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toString():      %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toStringHuman(): %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmssms::toStringHuman().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmssµs::toString():      %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmssµs::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmssµs::toStringHuman(): %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmssµs::toStringHuman().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmssns::toString():      %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmssns::toString().c_str());
    std::printf("dateAndTimeFunctions::UTC::YYYYMMDDhhmmssns::toStringHuman(): %s\n", dateAndTimeFunctions::UTC::YYYYMMDDhhmmssns::toStringHuman().c_str());

    return 0;
}
