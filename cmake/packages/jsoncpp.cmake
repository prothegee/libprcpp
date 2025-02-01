#[=[
jsoncpp

repo link: https://github.com/open-source-parsers/jsoncpp

===========================================

this library will use from vendors dir of "./vendors/jsoncpp"
#]=]
set(LIBPRCPP_PROJECT_USING_JSONCPP true) # always true since use project vendors

set(LIBPRCPP_VENDOR_JSONCPP_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/jsoncpp")

set(JSONCPP_WITH_TESTS false)
set(JSONCPP_WITH_EXAMPLE false)
set(JSONCPP_WITH_CMAKE_PACKAGE true)

add_subdirectory(${LIBPRCPP_VENDOR_JSONCPP_DIR} LIBPRCPP_JSONCPP)
