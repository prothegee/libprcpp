#[=[
libharu

repo link: https://github.com/libharu/libharu

===========================================

this library will use from vendors dir of "./vendors/libharu"
#]=]
set(LIBPRCPP_PROJECT_USING_LIBHARU true) # always true since use project vendors

set(LIBPRCPP_VENDOR_LIBHARU_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/libharu")
set(LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE ${LIBPRCPP_VENDOR_LIBHARU_DIR}/include)
set(LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE_OUT ${CMAKE_BINARY_DIR}/LIBPRCPP_LIBHARU/include)

set(LIBHPDF_SHARED false)
set(LIBHPDF_STATIC true)
set(LIBHPDF_EXAMPLES false)

add_subdirectory(${LIBPRCPP_VENDOR_LIBHARU_DIR} LIBPRCPP_LIBHARU)
include_directories(${LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE})
include_directories(${LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE_OUT})

message(NOTICE "-- libharu using project vendor dir as ${LIBPRCPP_VENDOR_LIBHARU_DIR}")
