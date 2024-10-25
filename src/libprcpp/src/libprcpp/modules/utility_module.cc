#include "utility_module.hh"

#include <regex>
#include <iostream>
#include <fstream>

#if PROJECT_BUILD_COMPILER_ID == 1
// RESERVED
#elif PROJECT_BUILD_COMPILER_ID == 2
#pragma warning (push)
#pragma warning (disable : 4996)
#pragma warning (disable : 4242)
#pragma warning (disable : 4244)
#elif PROJECT_BUILD_COMPILER_ID == 3
// RESERVED
#endif

namespace libprcpp
{
} // namespace libprcpp

#if PROJECT_BUILD_COMPILER_ID == 1
// RESERVED
#elif PROJECT_BUILD_COMPILER_ID == 2
#pragma warning (pop)
#elif PROJECT_BUILD_COMPILER_ID == 3
// RESERVED
#endif
