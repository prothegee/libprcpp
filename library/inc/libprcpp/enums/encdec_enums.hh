#ifndef LIBPRCPP_ENCDEC_ENUMS_HH
#define LIBPRCPP_ENCDEC_ENUMS_HH
#include <libprcpp/config.hh>
#include <libprcpp/types/base_types.hh>

namespace libprcpp
{

/**
 * @brief encrypt decrypt mode enum
 */
enum EEncDecMode : i32
{
    ENC_DEC_MODE_UNDEFINED,
#if LIBPRCPP_USING_OPENSSL
    ENC_DEC_MODE_AES_OPENSSL,
#endif // LIBPRCPP_USING_OPENSSL
#if LIBPRCPP_USING_CRYPTOPP_CMAKE
    ENC_DEC_MODE_AES_CRYPTOPP,
    ENC_DEC_MODE_XCHACHA20_CRYPTOPP,
    ENC_DEC_MODE_RC6_CRYPTOPP,
#endif // LIBPRCPP_USING_CRYPTOPP_CMAKE
};

} // namespace libprcpp

#endif // LIBPRCPP_ENCDEC_ENUMS_HH
