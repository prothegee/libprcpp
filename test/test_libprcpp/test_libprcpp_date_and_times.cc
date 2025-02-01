#include <libprcpp/functions/date_and_times_funcs.hh>

using namespace libprcpp;

int main()
{
    std::printf("start test for test_date_and_times\n");

    std::printf("dateAndTimesFunctions::UTC::year::toString():                  %s\n", dateAndTimesFunctions::UTC::year::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::month::toString():                 %s\n", dateAndTimesFunctions::UTC::month::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::day::toString():                   %s\n", dateAndTimesFunctions::UTC::day::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::hour::toString():                  %s\n", dateAndTimesFunctions::UTC::hour::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::minute::toString():                %s\n", dateAndTimesFunctions::UTC::minute::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::second::toString():                %s\n", dateAndTimesFunctions::UTC::second::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::timeZone::toString():              %s\n", dateAndTimesFunctions::UTC::timeZone::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDD::toString():              %s\n", dateAndTimesFunctions::UTC::YYYYMMDD::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDD::toStringISO8601():       %s\n", dateAndTimesFunctions::UTC::YYYYMMDD::toStringISO8601().c_str());
    std::printf("dateAndTimesFunctions::UTC::hhmmss::toString():                %s\n", dateAndTimesFunctions::UTC::hhmmss::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::hhmmss::toStringHuman():           %s\n", dateAndTimesFunctions::UTC::hhmmss::toStringHuman().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmss::toString():        %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmss::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmss::toStringHuman():   %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmss::toStringHuman().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toString():      %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toStringHuman(): %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmssms::toStringHuman().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmssµs::toString():      %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmssµs::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmssµs::toStringHuman(): %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmssµs::toStringHuman().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmssns::toString():      %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmssns::toString().c_str());
    std::printf("dateAndTimesFunctions::UTC::YYYYMMDDhhmmssns::toStringHuman(): %s\n", dateAndTimesFunctions::UTC::YYYYMMDDhhmmssns::toStringHuman().c_str());

    return 0;
}
