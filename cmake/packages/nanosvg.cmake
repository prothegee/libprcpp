#[=[
lunasvg

repo link: https://github.com/memononen/nanosvg

===========================================

this library will use from vendors dir of "./vendors/nanosvg"
#]=]
set(LIBPRCPP_PROJECT_USING_NANOSVG true) # always true since use project vendors

set(LIBPRCPP_VENDOR_NANOSVG_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/nanosvg")

add_subdirectory(${LIBPRCPP_VENDOR_NANOSVG_DIR} LIBPRCPP_NANOSVG)
include_directories(${LIBPRCPP_VENDOR_NANOSVG_DIR}/src)

message(NOTICE "-- nanosvg using project vendor dir as ${LIBPRCPP_VENDOR_NANOSVG_DIR}")
