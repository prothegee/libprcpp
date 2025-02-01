#[=[
zxing-cpp

repo link: https://github.com/zxing-cpp/zxing-cpp

===========================================

this library will use from vendors dir of "./vendors/zxing-cpp"
#]=]
set(LIBPRCPP_PROJECT_USING_ZXING_CPP true) # always true since use project vendors

set(LIBPRCPP_VENDOR_ZXING_CPP_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/zxing-cpp")

set(ZXING_EXPERIMENTAL_API true)
set(ZXING_EXAMPLES false)
set(ZXING_BLACKBOX_TESTS false)
set(ZXING_UNIT_TESTS false)

# make consistent ZXing dir to include
if(NOT EXISTS "${CMAKE_BINARY_DIR}/out/ZXing")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/out/ZXing")
endif()

set(LIBPRCPP_VENDOR_ZXING_CPP_DIR_OUT)

file(COPY "${LIBPRCPP_VENDOR_ZXING_CPP_DIR}/core/src/" DESTINATION "${CMAKE_BINARY_DIR}/out/ZXing")

set(LIBPRCPP_VENDOR_ZXING_CPP_DIR_OUT "${CMAKE_BINARY_DIR}/out")

include_directories(${LIBPRCPP_VENDOR_ZXING_CPP_DIR_OUT})

add_subdirectory(${LIBPRCPP_VENDOR_ZXING_CPP_DIR} LIBPRCPP_ZXING_CPP)

message(NOTICE "-- zxing-cpp using project vendor dir as ${LIBPRCPP_VENDOR_ZXING_CPP_DIR}")
