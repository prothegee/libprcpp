#ifndef LIBPRCPP_BASIC_TYPES_H
#define LIBPRCPP_BASIC_TYPES_H
#include <string>

namespace libprcpp
{

// alter type of int32_t
typedef int32_t TInt32;

// alter type of int64_t
typedef int64_t TInt64;

#ifndef UINT64_MAX
    #define UINT64_MAX 18446744073709551615ULL
#endif // UINT64_MAX

// alter type of uint32_t
typedef uint32_t TUInt32;

// alter type of uint64_t
typedef uint64_t TUInt64;

} // namespace libprcpp

#endif // LIBPRCPP_BASIC_TYPES_H
