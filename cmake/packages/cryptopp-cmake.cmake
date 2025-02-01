#[=[
cryptopp

repo link: https://github.com/abdes/cryptopp-cmake
#]=]
set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE true)

set(LIBPRCPP_VENDOR_CRYPTOPP_CMAKE_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/cryptopp-cmake")

set(CRYPTOPP_BUILD_TESTING false)

add_subdirectory(${LIBPRCPP_VENDOR_CRYPTOPP_CMAKE_DIR} LIBPRCPP_CRYPTOPP_CMAKE)
