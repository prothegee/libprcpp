#ifndef PRGENT_ARGS_CONST_HH
#define PRGENT_ARGS_CONST_HH
#include <libprcpp/types/basic_types.hh>

using namespace libprcpp;

namespace prgent
{

inline static cchar *ARG_IS_HELP = "--help"; // arg for `--help`
inline static cchar *ARG_IS_MODE = "--mode"; // arg for `--mode`
inline static cchar *ARG_IS_INPUT = "--input"; // arg for `--input`
inline static cchar *ARG_IS_OUTPUT = "--output"; // arg for `--output`
inline static cchar *ARG_IS_OUTPUT_DIR = "--output-dir"; // arg for `--output-dir`
inline static cchar *ARG_IS_OUTPUT_EXT = "--output-ext"; // arg for `--output-ext`
inline static cchar *ARG_IS_IMAGE_SIZE = "--image-size"; // arg for `--image-size` apply NNNxNNN where N is numeric value
inline static cchar *ARG_IS_IMAGE_WIDTH = "--image-width"; // arg for `--image-width`
inline static cchar *ARG_IS_IMAGE_HEIGHT = "--image-height"; // arg for `--image-height`
inline static cchar *ARG_IS_IMAGE_MARGIN = "--image-height"; // arg for `--image-margin`

} // namespace prgent

#endif // PRGENT_ARGS_CONST_HH
