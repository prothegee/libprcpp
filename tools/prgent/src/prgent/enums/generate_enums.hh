#ifndef PRGENT_GENERATE_ENUMS_HH
#define PRGENT_GENERATE_ENUMS_HH
#include <libprcpp/types/basic_types.hh>

using namespace libprcpp;

namespace prgent
{

/**
 * @brief prgent generate mode enum
 */
enum EGenerateMode : i32
{
    GENERATE_MODE_UNDEFINED,
    GENERATE_MODE_BARCODE_FROM_TEXT,
    GENERATE_MODE_BARCODE_DECODE,
    GENERATE_MODE_QRCODE_FROM_TEXT,
    GENERATE_MODE_QRCODE_DECODE,
};

} // namespace prgent

#endif // PRGENT_GENERATE_ENUMS_HH
