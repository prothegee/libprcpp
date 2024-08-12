#ifndef LIBPRCPP_ENCDEC_ENUMS_H
#define LIBPRCPP_ENCDEC_ENUMS_H
#include <libprcpp/types/basic_types.h>

namespace libprcpp
{

/**
 * @brief enum encrypt decrypt mode structure
 * 
 */
struct EEncDecMode
{
    /**
     * @brief enum object for EEncDecMode
     * 
     */
    enum Enum : TInt32
    {
        ENC_DEC_MODE_UNDEFINED = 0,
        ENC_DEC_MODE_OPENSSL_AES,
    };
};

} // namespace libprcpp

#endif // LIBPRCPP_ENCDEC_ENUMS_H
