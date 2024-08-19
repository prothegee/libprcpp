#ifndef LIBPRCPP_ENCDEC_ENUMS_H
#define LIBPRCPP_ENCDEC_ENUMS_H
#include <libprcpp/base/config.h>
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
    #if LIBPRCPP_PROJECT_USING_OPENSSL
        ENC_DEC_MODE_AES_OPENSSL = 1,
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        // ENC_DEC_MODE_AES_CRYPTOPP = 2, // RESERVED
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    };
};

} // namespace libprcpp

#endif // LIBPRCPP_ENCDEC_ENUMS_H
