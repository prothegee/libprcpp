#[=[
jsoncpp

repo link: https://github.com/open-source-parsers/jsoncpp

===========================================

if current machine not providing the library,
this library will use from vendors dir of "./vendors/jsoncpp"
#]=]
set(LIBPRCPP_PROJECT_USING_JSONCPP false)

find_package(jsoncpp CONFIG)

if(jsoncpp_FOUND)
    set(LIBPRCPP_PROJECT_USING_JSONCPP true)

    message(NOTICE "-- jsoncpp package found")
else()
    set(LIBPRCPP_PROJECT_USING_JSONCPP true)
    set(LIBPRCPP_VENDOR_JSONCPP_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/jsoncpp")

    set(JSONCPP_WITH_TESTS false)
    set(JSONCPP_WITH_EXAMPLE false)
    set(JSONCPP_WITH_CMAKE_PACKAGE true)

    add_subdirectory(${LIBPRCPP_VENDOR_JSONCPP_DIR} LIBPRCPP_JSONCPP)

    message(NOTICE "-- jsoncpp using project vendor dir as ${LIBPRCPP_VENDOR_JSONCPP_DIR}")
endif()
