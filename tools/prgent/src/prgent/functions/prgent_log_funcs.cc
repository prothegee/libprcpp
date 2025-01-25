#include "prgent_log_funcs.hh"

#include "../constants/generate_const.hh"

#include <iostream>

#include <libprcpp/base/config.hh>

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
    std::printf("--help: show this help message\n    - to show supported mode usage use \"--help mode\"\n");
    std::printf("--mode: specify the mode use number or string\n    - e.g.: 1:barcode-encode 3:qrcode-encode\n");
    std::printf("--input: input file path\n");
    std::printf("--output: output file path\n");
    std::printf("--output-dir: output directory/folder\n");
    std::printf("--output-ext: output extension name\n   - encode barcode & qrcode, only supported .svg, .png, .jpg, .jpeg, use .svg by default if not supply\n");
    std::printf("--image-size: specify image size in NNNxNNN format, where N is must numeric as pixel/px\n   - 256x256 px is default size\n   - .svg will ignore size\n");
    std::printf("--image-margin: specify margin of image\n   - only support for barcode & qrcode encode\n");
    std::printf("--batch-iter: create batch iteration from value of number\n   - only allowed number\n   - can't be less/equal to 0\n   - only support for barcode & qrcode encode\n");
    std::printf("--batch-out-csv: create output of batch record to csv file\n   - only apply if true");
    std::printf("--batch-out-json: create output of batch record to json file\n   - only apply if true");
}

void showHelpConfigurations(const std::string &helpHint)
{
    std::printf("TODO: help is using arg of %s", helpHint.c_str());
    #if LIBPRCPP_COMPILER_MSVC
    #pragma message ("TODO: help is using arg of helpHint param")
    #else
    #pragma message "TODO: help is using arg of helpHint param"
    #endif // LIBPRCPP_COMPILER_MSVC
}

} // namespace log
} // namespace prgent
