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
    #pragma message("TODO: specify this")
    std::printf("prgent usage:\n");
    std::printf("--help: show this help message\n    - use --help mode to show supported mode usage\n");
    std::printf("--mode: specify the mode use number or string\n    - e.g.: 1:barcode-encode 3:qrcode-encode\n");
    std::printf("--input: input file path\n");
    std::printf("--output: output file path\n");
}

void showHelpConfigurations(const std::string &helpHint)
{
    std::printf("TODO: help is using arg of %s", helpHint.c_str());
}

} // namespace log
} // namespace prgent
