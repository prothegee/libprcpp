#[=[
jsoncpp

repo link: https://github.com/open-source-parsers/jsoncpp
#]=]
set(LIBPRCPP_PROJECT_USING_JSONCPP true)

set(LIBPRCPP_VENDOR_JSONCPP_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/jsoncpp")

set(JSONCPP_WITH_TESTS false)
set(JSONCPP_WITH_EXAMPLE false)
set(JSONCPP_WITH_CMAKE_PACKAGE true)

include_directories(${LIBPRCPP_VENDOR_JSONCPP_DIR}/include)

add_subdirectory(${LIBPRCPP_VENDOR_JSONCPP_DIR} LIBPRCPP_JSONCPP)

link_directories(AFTER "${CMAKE_BINARY_DIR}/LIBPRCPP_JSONCPP/src/lib_json")

message(NOTICE "-- jsoncpp using project vendor dir as ${LIBPRCPP_VENDOR_JSONCPP_DIR}")
