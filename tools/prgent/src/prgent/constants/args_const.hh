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
inline static cchar *ARG_IS_IMAGE_MARGIN = "--image-margin"; // arg for `--image-margin`
inline static cchar *ARG_IS_BATCH_ITER = "--batch-iter"; // arg for `--image-margin`
inline static cchar *ARG_IS_BATCH_OUT_CSV = "--batch-out-csv"; // arg for `--batch-out-csv`
inline static cchar *ARG_IS_BATCH_OUT_JSON = "--batch-out-json"; // arg for `--batch-out-json`

} // namespace prgent

#endif // PRGENT_ARGS_CONST_HH
