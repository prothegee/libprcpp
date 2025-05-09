#ifndef LIBPRCPP_BASE_TYPES_HH
#define LIBPRCPP_BASE_TYPES_HH
#include <cstdint>
#include <vector>

#ifndef UINT64_MAX
    #define UINT64_MAX 18446744073709551615ULL
#endif // UINT64_MAX

#ifndef LIBPRCPP_TRUE_BUT_STRING
    // yes, it's "true"
    #define LIBPRCPP_TRUE_BUT_STRING "true"
#endif // LIBPRCPP_TRUE_BUT_STRING

#ifndef LIBPRCPP_FALSE_BUT_STRING
    // no, it's "false"
    #define LIBPRCPP_FALSE_BUT_STRING "false"
#endif // LIBPRCPP_FALSE_BUT_STRING

namespace libprcpp
{

// alter type of int32_t
typedef int32_t TI32;

// alter type of int64_t
typedef int64_t TI64;

// alter type of int128_t
typedef __int128_t TI128;

// alter type of uint32_t
typedef uint32_t TU32;

// alter type of uint64_t
typedef uint64_t TU64;

// alter type of uint128_t
typedef __uint128_t TU128;

// alter type of float
typedef float TF32;

// alter type of double
typedef double TF64;

// alter type of char
typedef char TChr;

// alter type of unsigned char
typedef unsigned char TUChr;

// buffer type, alter of std::vector<unsigned char> 
typedef std::vector<unsigned char> TBuffer;

} // namespace libprcpp

#endif // LIBPRCPP_BASE_TYPES_HH
