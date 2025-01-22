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

#endif // PRGENT_BARCODE_FUNCS_HH
