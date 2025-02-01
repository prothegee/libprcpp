#ifndef PRGENT_FILE_EXTENSION_ENUMS_HH
#define PRGENT_FILE_EXTENSION_ENUMS_HH
#include <libprcpp/types/basic_types.hh>

using namespace libprcpp;

namespace prgent
{

/**
 * @brief prgent file extension enum
 */
enum EFileExtension : i32
{
    FILE_EXTENSION_IS_UNDEFINED,
    FILE_EXTENSION_IS_JPEG,
    FILE_EXTENSION_IS_JPG,
    FILE_EXTENSION_IS_PDF,
    FILE_EXTENSION_IS_PNG,
    FILE_EXTENSION_IS_SVG,
};

} // namespace prgent

#endif // PRGENT_FILE_EXTENSION_ENUMS_HH
