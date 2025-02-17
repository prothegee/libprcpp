#ifndef LIBPRCPP_IMAGES_FUNCS_HH
#define LIBPRCPP_IMAGES_FUNCS_HH
#include <libprcpp/config.hh>
#include <libprcpp/export.hh>
#include <libprcpp/constants/files_const.hh>
#include <libprcpp/types/base_types.hh>

#if LIBPRCPP_USING_ZXING_CPP
#include <ZXing/BarcodeFormat.h>
#include <ZXing/BitMatrix.h>
#include <ZXing/BitMatrixIO.h>
#include <ZXing/CharacterSet.h>
#include <ZXing/TextUtfEncoding.h>
#include <ZXing/MultiFormatWriter.h>
#include <ZXing/ReadBarcode.h>
#include <ZXing/ReaderOptions.h>
#include <ZXing/DecodeHints.h>
#include <ZXing/ImageView.h>

#if ZXING_EXPERIMENTAL_API
#include <ZXing/WriteBarcode.h>
#endif // ZXING_EXPERIMENTAL_API
#endif // LIBPRCPP_USING_ZXING_CPP

// #if LIBPRCPP_USING_LUNASVG
// #include <lunasvg.h>
// #endif // LIBPRCPP_USING_LUNASVG

#if LIBPRCPP_USING_NANOSVG
#include <nanosvg/nanosvg.h>
#include <nanosvg/nanosvgrast.h>
#endif // LIBPRCPP_USING_NANOSVG

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace ZXing;

namespace libprcpp
{
namespace imagesFunctions
{


namespace generate
{
    /**
     * @brief generate svg image from buffer to output
     * 
     * @param output required .svg on the last output param
     * @param matrix 
     * @param width 
     * @param height 
     * @param margin 
     * @return true ok
     * @return false fail
     */
    bool toSVG(const std::string &output, const BitMatrix &matrix, const int32_t &width, const int32_t &height, const int32_t &margin);

    /**
     * @brief generate png image from buffer to output
     * 
     * @param output required .png on the last output param
     * @param buffer 
     * @param x 
     * @param y 
     * @param comp 
     * @return true ok
     * @return false fail
     */
    bool toPNG(const std::string &output, const TBuffer &buffer, const int32_t &x, const int32_t &y, const int32_t &comp = 4);

    /**
     * @brief generate jpg/jpeg image from buffer to output
     * 
     * @param output required .jpg/.jpeg on the last output param
     * @param buffer 
     * @param x 
     * @param y 
     * @param comp 
     * @return true ok
     * @return false fail
     */
    bool toJPG(const std::string &output, const TBuffer &buffer, const int32_t &x, const int32_t &y, const int32_t &comp = 4);
} // namespace generate


namespace rasterize
{
    /**
     * @brief rasterize bitmap data to output from svgPath param
     * 
     * @note important: size of width & height if less than 256 may cause a trouble
     * 
     * @param svgPath 
     * @param output 
     * @param width 
     * @param height 
     * @return true ok
     * @return false fail
     */
    bool fromSVG(const std::string &svgPath, std::vector<uint8_t> &output, int32_t &width, int32_t &height);
} // namespace rasterize


namespace barcode
{
    /**
     * @brief encode barcode
     * 
     * @note consider use try catch
     * @note important: size of width & height if less than 256 may cause a trouble
     * @note important: considering use std::thread or std::asyc is recomended, it can cause invalid pointer if the usage is more than once in the same implementation
     * 
     * @param content 
     * @param output 
     * @param width 
     * @param height 
     * @param margin 
     * @param codeFormat 
     * @return true ok
     * @return false fail
     */
    bool encode(const std::string &content, const std::string &output, const int32_t &width, const int32_t &height, const int32_t &margin, const BarcodeFormat &codeFormat = BarcodeFormat::Code128);

    /**
     * @brief decode barcode
     * 
     * @note consider use try catch
     * @note important: size of width & height if less than 256 may cause a trouble
     * 
     * @param content 
     * @param output 
     * @param codeFormat 
     * @param tryHard 
     * @return true ok
     * @return false fail
     */
    bool decode(const std::string &content, std::string &output, const BarcodeFormat &codeFormat = BarcodeFormat::Code128, const bool &tryHard = true);
} // namespace barcode


namespace qrcode
{
    /**
     * @brief encode qrcode
     * 
     * @note consider use try catch
     * @note important: size of width & height if less than 256 may cause a trouble
     * @note important: considering use std::thread or std::asyc is recomended, it can cause invalid pointer if the usage is more than once in the same implementation
     * 
     * @param content 
     * @param output 
     * @param width 
     * @param height 
     * @param margin 
     * @param codeFormat 
     * @return true ok
     * @return false fail
     */
    bool encode(const std::string &content, const std::string &output, const int32_t &width, const int32_t &height, const int32_t &margin, const BarcodeFormat &codeFormat = BarcodeFormat::QRCode);

    /**
     * @brief decode qrcode
     * 
     * @note consider use try catch
     * @note important: size of width & height if less than 256 may cause a trouble
     * 
     * @param content 
     * @param output 
     * @param codeFormat 
     * @param tryHard 
     * @return true 
     * @return false 
     */
    bool decode(const std::string &content, std::string &output, const BarcodeFormat &codeFormat = BarcodeFormat::QRCode, const bool &tryHard = true);
} // namespace qrcode


} // namespace imagesFunctions
} // namespace libprcpp

#endif // LIBPRCPP_IMAGES_FUNCS_HH
