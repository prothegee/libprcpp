#ifndef PRGENT_BARCODE_FUNCS_HH
#define PRGENT_BARCODE_FUNCS_HH
#include <libprcpp/base/config.hh>
#include <libprcpp/types/basic_types.hh>
#include <libprcpp/functions/common_funcs.hh>

using namespace libprcpp;

namespace prgent
{
namespace barcode
{

/**
 * @brief decode/read barcode content
 * 
 * @note there's no sanity check for width & height for content image, do verify first before using this function
 * @note some image with less than 256 may cause error
 * @note may similar with qrcode::decodeImage, but it's preserve for barcode
 * 
 * @param content 
 * @param output data to pass
 * @return true 
 * @return false 
 */
bool decodeImage(const std::string &content, std::string &output);

/**
 * @brief encode/generate barcode as image
 * 
 * @param content 
 * @param output 
 * @param width 
 * @param height 
 * @param margin 
 * @return true 
 * @return false 
 */
bool encodeImage(const std::string &content, const std::string &output, const i32 &width, const i32 &height, const i32 &margin);

} // namespace barcode
} // namespace prgent

#endif // PRGENT_BARCODE_FUNCS_HH
