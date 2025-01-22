#ifndef PRGENT_IMAGE_GEN_FUNCS_HH
#define PRGENT_IMAGE_GEN_FUNCS_HH
#include <libprcpp/base/config.hh>
#include <libprcpp/types/basic_types.hh>
#include <libprcpp/functions/common_funcs.hh>

#include <prgent/constants/file_extension_const.hh>

#if LIBPRCPP_PROJECT_USING_ZXING
#include <ZXing/BarcodeFormat.h>
#include <ZXing/BitMatrix.h>
#include <ZXing/BitMatrixIO.h>
#include <ZXing/CharacterSet.h>
#include <ZXing/TextUtfEncoding.h>
#include <ZXing/MultiFormatWriter.h>
#include <ZXing/BarcodeFormat.h>
#include <ZXing/Version.h>

#if ZXING_EXPERIMENTAL_API
#include <ZXing/WriteBarcode.h>
#endif // ZXING_EXPERIMENTAL_API

using namespace ZXing;
using namespace libprcpp;

namespace prgent
{

/**
 * @brief generate svg image
 * 
 * @param output 
 * @param matrix 
 * @param width 
 * @param height 
 * @param margin 
 * @return true 
 * @return false 
 */
bool generateSVG(const char *output, const BitMatrix &matrix, const i32 &width, const i32 &height, const i32 &margin);

} // namespace prgent

#endif // LIBPRCPP_PROJECT_USING_ZXING

#endif // PRGENT_IMAGE_GEN_FUNCS_HH
