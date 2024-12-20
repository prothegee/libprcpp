#ifndef LIBPRCPP_ENCDEC_ENUMS_HH
#define LIBPRCPP_ENCDEC_ENUMS_HH
#include <libprcpp/base/config.hh>
#include <libprcpp/types/basic_types.hh>

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
    enum ENUM : i32
    {
        ENC_DEC_MODE_UNDEFINED,
    #if LIBPRCPP_PROJECT_USING_OPENSSL
        ENC_DEC_MODE_AES_OPENSSL,
    #endif // LIBPRCPP_PROJECT_USING_OPENSSL
    #if LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
        ENC_DEC_MODE_AES_CRYPTOPP,
        ENC_DEC_MODE_XCHACHA20_CRYPTOPP,
        ENC_DEC_MODE_RC6_CRYPTOPP,
    #endif // LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE
    };
};

} // namespace libprcpp

#endif // LIBPRCPP_ENCDEC_ENUMS_HH
