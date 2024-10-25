#ifndef LIBPRCPP_UTILITY_MODULE_HH
#define LIBPRCPP_UTILITY_MODULE_HH
#include <libprcpp/base/config.hh>
#include <libprcpp/base/export.hh>

#include <libprcpp/enums/requirement_enums.hh>
#include <libprcpp/enums/time_enums.hh>

#include <string>
#include <random>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <ctime>
#include <chrono>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <array>

#if LIBPRCPP_PROJECT_USING_OPENSSL
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#endif // LIBPRCPP_PROJECT_USING_OPENSSL

#if PROJECT_BUILD_COMPILER_ID == 1
// RESERVED
#elif PROJECT_BUILD_COMPILER_ID == 2
#pragma warning (push)
#pragma warning (disable : 4996)
#pragma warning (disable : 4244)
#elif PROJECT_BUILD_COMPILER_ID == 3
// RESERVED
#endif

namespace libprcpp
{
} // namespace libprcpp

#endif // LIBPRCPP_UTILITY_MODULE_HH
