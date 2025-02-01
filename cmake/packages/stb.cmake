#[=[
stb

repo link: https://github.com/nothings/stb

===========================================

this library will use from vendors dir of "./vendors/stb"
#]=]
set(LIBPRCPP_PROJECT_USING_STB false)
set(LIBPRCPP_PROJECT_USING_STB_HAS_PARENT_DIR false)

if(NOT DEFINED ${Stb_INCLUDE_DIR})
    set(Stb_INCLUDE_DIR "")
endif()

set(LIBPRCPP_VENDOR_STB_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/stb")

if(NOT ${LIBPRCPP_VENDOR_STB_DIR} STREQUAL "")
    set(Stb_INCLUDE_DIR ${LIBPRCPP_VENDOR_STB_DIR})
    include_directories(${Stb_INCLUDE_DIR})
    set(LIBPRCPP_PROJECT_USING_STB true)
    message(NOTICE "-- stb lib using project vendor dir as ${LIBPRCPP_VENDOR_STB_DIR}")
endif()

