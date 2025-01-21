#include "prgent_log_funcs.hh"

#include "../constants/generate_const.hh"

#include <iostream>

namespace prgent
{
namespace log
{
void okBase()
{
    std::printf("# prgent ok:\n");
}

void errorBase()
{
    std::printf("# prgent error:\n");
}

void noticeBase()
{
    std::printf("# prgent notice:\n");
}

void warningBase()
{
    std::printf("# prgent warning:\n");
}

void showHelpBaseHint()
{
    std::printf("prgent usage:\n");
    std::printf("--help: show this help message\n");
    std::printf("--mode: specify the mode (e.g., barcode or qr code)\n");
    std::printf("--input: input file path\n");
    std::printf("--output: output file path\n");
}

void showHelpConfigurations(const std::string &helpHint)
{
    std::printf("TODO: help is using arg of %s", helpHint.c_str());
}

} // namespace log
} // namespace prgent
