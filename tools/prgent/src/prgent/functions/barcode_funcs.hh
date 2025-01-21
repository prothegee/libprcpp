#ifndef PRGENT_BARCODE_FUNCS_HH
#define PRGENT_BARCODE_FUNCS_HH
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

#if LIBPRCPP_PROJECT_USING_STB
#include <stb/stb_image_write.h>
#endif // LIBPRCPP_PROJECT_USING_STB

using namespace libprcpp;
using namespace ZXing;

namespace prgent
{
namespace barcode
{

/**
 * @brief encode/generate barcode as image
 * 
 * @param content 
 * @param output 
 * @param width 
 * @param height 
 * @param margin 
 * @return true ok,
 * @return false fail
 */
bool encodeImage(const std::string &content, const std::string &output, const i32 &width, const i32 &height, const i32 &margin);

} // namespace barcode
} // namespace prgent

#endif // LIBPRCPP_PROJECT_USING_ZXING

#endif // PRGENT_BARCODE_FUNCS_HH
