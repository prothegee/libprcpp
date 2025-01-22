#ifndef PRGENT_GENERATE_CONST_HH
#define PRGENT_GENERATE_CONST_HH
#include <libprcpp/types/basic_types.hh>

using namespace libprcpp;

namespace prgent
{

inline static cchar *GENERATE_MODE_BARCODE_ENCODE_ARG_AS_NUM = "1"; // "1"
inline static cchar *GENERATE_MODE_BARCODE_ENCODE_ARG_AS_STR = "barcode-encode"; // "barcode-encode"

inline static cchar *GENERATE_MODE_BARCODE_DECODE_AS_NUM = "2"; // "2"
inline static cchar *GENERATE_MODE_BARCODE_DECODE_AS_STR = "barcode-decode"; // "barcode-decode"

inline static cchar *GENERATE_MODE_QRCODE_ENCODE_ARG_AS_NUM = "3"; // "3"
inline static cchar *GENERATE_MODE_QRCODE_ENCODE_ARG_AS_STR = "qrcode-encode"; // "qrcode-encode"

inline static cchar *GENERATE_MODE_QRCODE_DECODE_AS_NUM = "4"; // "4"
inline static cchar *GENERATE_MODE_QRCODE_DECODE_AS_STR = "qrcode-decode"; // "qrcode-decode"

} // namespace prgent

#endif // PRGENT_GENERATE_CONST_HH
