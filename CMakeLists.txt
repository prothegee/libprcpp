cmake_minimum_required(VERSION 3.15...3.30)


# versions
set(LIBPRCPP_VERSION_MAJOR  0)
set(LIBPRCPP_VERSION_MINOR  16)
set(LIBPRCPP_VERSION_PATCH  0)
set(LIBPRCPP_VERSION_DATES  20250315)
set(LIBPRCPP_VERSION_BUILD "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}.${LIBPRCPP_VERSION_DATES}")


# project
# project(libprcpp)
project(libprcpp
    VERSION "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}"
    DESCRIPTION "one stop c++ library for c++ project, currently for personal use as module"
    HOMEPAGE_URL "https://github.com/prothegee/libprcpp"
    LANGUAGES CXX C
)

set(LIBPRCPP_PROJECT_DIR ${PROJECT_SOURCE_DIR})


# option/s
## build tools, default false/OFF
option(BUILD_TOOLS              "build project tool/s" OFF)
## build tests, default false/OFF
option(BUILD_TESTS              "build project test/s" OFF)
## build use vcpkg
option(BUILD_USE_VCPKG          "build using vcpkg, will look environment variable of VCPKG_DIR/VCPKG_ROOT & VCPKG_DEFAULT_TRIPLET/DEFAULT_TRIPLET" OFF)
# ## build as shared libs, default false/OFF
# option(BUILD_SHARED_LIBS        "build as shared library" OFF) # skip for now

## skipped vendor SDL lib, default true/ON
option(BUILD_SKIPPED_VENDOR_SDL             "build skipped for SDL" OFF)
## skipped vendor STB lib, default true/ON
option(BUILD_SKIPPED_VENDOR_STB             "build skipped for STB" OFF)
## skipped vendor libharu/hpdf lib, default true/ON
option(BUILD_SKIPPED_VENDOR_LIBHARU         "build skipped for libharu/hpdf" OFF)
## skipped vendor nanosvg lib, default false/OFF
option(BUILD_SKIPPED_VENDOR_NANOSVG         "build skipped for nanosvg" OFF)
## skipped vendor zxing-cpp lib, default false/OFF
option(BUILD_SKIPPED_VENDOR_ZXING_CPP       "build skipped for zxing-cpp" OFF)
## skipped vendor cryptopp-cmake lib, default false/OFF
option(BUILD_SKIPPED_VENDOR_CRYPTOPP_CMAKE  "build skipped for cryptopp-cmake" OFF)


# variables
## build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

## cxx standard required
if(NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

## cxx standard
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

## libprcpp system name
if(NOT DEFINED LIBPRCPP_SYSTEM_NAME)
    set(LIBPRCPP_SYSTEM_NAME "")
endif()
string(TOLOWER "${CMAKE_SYSTEM_NAME}" LIBPRCPP_SYSTEM_NAME)

## libprcpp system processor
if(NOT DEFINED LIBPRCPP_SYSTEM_PROCESSOR)
    set(LIBPRCPP_SYSTEM_PROCESSOR "")
endif()
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" LIBPRCPP_SYSTEM_PROCESSOR)

## libprcpp system build type
if(NOT DEFINED LIBPRCPP_SYSTEM_BUILD_TYPE)
    set(LIBPRCPP_SYSTEM_BUILD_TYPE "")
endif()
string(TOLOWER "${CMAKE_BUILD_TYPE}" LIBPRCPP_SYSTEM_BUILD_TYPE)

## libprcpp system processor out
if(NOT DEFINED LIBPRCPP_SYSTEM_PROCESSOR_OUT)
    set(LIBPRCPP_SYSTEM_PROCESSOR_OUT "unknown")
endif()
if(LIBPRCPP_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(LIBPRCPP_SYSTEM_PROCESSOR_OUT "x86_64")
elseif(LIBPRCPP_SYSTEM_PROCESSOR STREQUAL "amd64")
    set(LIBPRCPP_SYSTEM_PROCESSOR_OUT "x86_64")
elseif(LIBPRCPP_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(LIBPRCPP_SYSTEM_PROCESSOR_OUT "arm64")
elseif(LIBPRCPP_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(LIBPRCPP_SYSTEM_PROCESSOR_OUT "arm64")
else()
    message(WARNING "-- ${PROJECT_NAME}: processor type is not supported `${LIBPRCPP_SYSTEM_PROCESSOR}`")
endif()

## compiler id
if(NOT DEFINED LIBPRCPP_COMPILER_ID)
    # 0:undefined
    # 1:gnu
    # 2:msvc
    # 3:clang
    set(LIBPRCPP_COMPILER_ID 0)
endif()

## build target
### [V] 0:undefined
### [V] 1:linux
### [V] 2:windows
### [V] 3:macos
### [X] 4:android
### [X] 5:ios
### [X] 6:web
### [X] 7:ps
### [X] 8:xbox
### [X] 9:nintendo
if(NOT DEFINED LIBPRCPP_BUILD_TARGET)
    set(LIBPRCPP_BUILD_TARGET 0)
endif()

if(${LIBPRCPP_SYSTEM_NAME} STREQUAL "linux")
    set(LIBPRCPP_BUILD_TARGET 1)
elseif(${LIBPRCPP_SYSTEM_NAME} STREQUAL "windows")
    set(LIBPRCPP_BUILD_TARGET 2)
elseif(${LIBPRCPP_SYSTEM_NAME} STREQUAL "macos")
    set(LIBPRCPP_BUILD_TARGET 3)
else()
    message(NOTICE "-- ${PROJECT_NAME}: build system is unknown")
endif()

if(${LIBPRCPP_SYSTEM_NAME} STREQUAL "darwin")
    set(LIBPRCPP_BUILD_TARGET 3)
    set(LIBPRCPP_SYSTEM_NAME "macos")
endif()

## build status
### 0:undefined 1:debug 2:staging 3:demo 4:release
if(NOT DEFINED LIBPRCPP_BUILD_STATUS)
    set(LIBPRCPP_BUILD_STATUS 0)
endif()
if(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "debug")
    set(LIBPRCPP_BUILD_STATUS 1)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "profile")
    set(LIBPRCPP_BUILD_STATUS 1)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "relwithdebinfo")
    set(LIBPRCPP_BUILD_STATUS 2)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "release")
    set(LIBPRCPP_BUILD_STATUS 3)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "minsizerel")
    set(LIBPRCPP_BUILD_STATUS 4)
endif()

## is debug
if(NOT DEFINED LIBPRCPP_IS_DEBUG)
    set(LIBPRCPP_IS_DEBUG false)
endif()
if(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "release")
    set(LIBPRCPP_IS_DEBUG false)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "minsizerel")
    set(LIBPRCPP_IS_DEBUG false)
else()
    set(LIBPRCPP_IS_DEBUG true)
endif()

## libprcpp headers files
if(NOT DEFINED LIBPRCPP_HEADERS_FILES)
    set(LIBPRCPP_HEADERS_FILES)
endif()

## libprcpp sources files
if(NOT DEFINED LIBPRCPP_SOURCES_FILES)
    set(LIBPRCPP_SOURCES_FILES)
endif()


# include base
include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)


# libprcpp headers files specifier
## base
set(LIBPRCPP_HEADERS_FILES_BASE
    library/inc/libprcpp/config.hh
    library/inc/libprcpp/libprcpp.hh
)
list(APPEND LIBPRCPP_HEADERS_FILES ${LIBPRCPP_HEADERS_FILES_BASE})

## constants
set(LIBPRCPP_HEADERS_FILES_CONSTANTS
    library/inc/libprcpp/constants/files_const.hh
    library/inc/libprcpp/constants/header_const.hh
    library/inc/libprcpp/constants/host_const.hh
    library/inc/libprcpp/constants/return_const.hh
    library/inc/libprcpp/constants/strings_const.hh
)
list(APPEND LIBPRCPP_HEADERS_FILES ${LIBPRCPP_HEADERS_FILES_CONSTANTS})

## enums
set(LIBPRCPP_HEADERS_FILES_ENUMS
    library/inc/libprcpp/enums/encdec_enums.hh
    library/inc/libprcpp/enums/language_enums.hh
    library/inc/libprcpp/enums/result_enums.hh
    library/inc/libprcpp/enums/scylla_enums.hh
)
list(APPEND LIBPRCPP_HEADERS_FILES ${LIBPRCPP_HEADERS_FILES_ENUMS})

## functions
set(LIBPRCPP_HEADERS_FILES_FUNCTIONS
    library/inc/libprcpp/functions/cryptography_funcs.hh
    library/inc/libprcpp/functions/date_and_times_funcs.hh
    library/inc/libprcpp/functions/images_funcs.hh
    library/inc/libprcpp/functions/network_funcs.hh
    library/inc/libprcpp/functions/system_funcs.hh
    library/inc/libprcpp/functions/utility_funcs.hh
)
list(APPEND LIBPRCPP_HEADERS_FILES ${LIBPRCPP_HEADERS_FILES_FUNCTIONS})

## interfaces
set(LIBPRCPP_HEADERS_FILES_INTERFACES
    library/inc/libprcpp/interfaces/idrogon_http_controller_helper.hh
    library/inc/libprcpp/interfaces/ipostgresql_core_interface.hh
    library/inc/libprcpp/interfaces/iscylladb_core_interface.hh
)
list(APPEND LIBPRCPP_HEADERS_FILES ${LIBPRCPP_HEADERS_FILES_INTERFACES})

## types
set(LIBPRCPP_HEADERS_FILES_TYPES
    library/inc/libprcpp/types/auth_types.hh
    library/inc/libprcpp/types/base_types.hh
    library/inc/libprcpp/types/batch_types.hh
    library/inc/libprcpp/types/look_types.hh
    library/inc/libprcpp/types/postgresql_types.hh
    library/inc/libprcpp/types/scylla_types.hh
)
list(APPEND LIBPRCPP_HEADERS_FILES ${LIBPRCPP_HEADERS_FILES_TYPES})


# libprcpp sources files specifier
## base
set(LIBPRCPP_SOURCES_FILES_BASE
    library/src/libprcpp/libprcpp.cc
)
list(APPEND LIBPRCPP_SOURCES_FILES ${LIBPRCPP_SOURCES_FILES_BASE})

## functions
set(LIBPRCPP_SOURCES_FILES_FUNCTIONS
    library/src/libprcpp/functions/cryptography_funcs.cc
    library/src/libprcpp/functions/date_and_times_funcs.cc
    library/src/libprcpp/functions/images_funcs.cc
    library/src/libprcpp/functions/network_funcs.cc
    library/src/libprcpp/functions/system_funcs.cc
    library/src/libprcpp/functions/utility_funcs.cc
)
list(APPEND LIBPRCPP_SOURCES_FILES ${LIBPRCPP_SOURCES_FILES_FUNCTIONS})

## interfaces
set(LIBPRCPP_SOURCES_FILES_INTERFACES
    library/src/libprcpp/interfaces/idrogon_http_controller_helper.cc
    library/src/libprcpp/interfaces/ipostgresql_core_interface.cc
    library/src/libprcpp/interfaces/iscylladb_core_interface.cc
)
list(APPEND LIBPRCPP_SOURCES_FILES ${LIBPRCPP_SOURCES_FILES_INTERFACES})


# packages & their variables
## base toolchain
if(NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    message(NOTICE "-- ${PROJECT_NAME}: using CMAKE_TOOLCHAIN_FILE as `${CMAKE_TOOLCHAIN_FILE}`")
endif()

## base vcpkg
set(LIBPRCPP_USING_VCPKG false)
if(BUILD_USE_VCPKG)
    set(LIBPRCPP_VCPKG_DIR "")
    set(LIBPRCPP_VCPKG_TRIPLET "")
    set(LIBPRCPP_VCPKG_INSTALLED_DIR "")

    # check VCPKG_DIR env. var.
    if(NOT "$ENV{VCPKG_DIR}" STREQUAL "")
        set(LIBPRCPP_VCPKG_DIR "$ENV{VCPKG_DIR}")
    endif()

    # check VCPKG_ROOT env. var.
    if(NOT "$ENV{VCPKG_ROOT}" STREQUAL "")
        set(LIBPRCPP_VCPKG_DIR "$ENV{VCPKG_ROOT}")
    endif()

    if(BUILD_USE_VCPKG AND LIBPRCPP_VCPKG_DIR STREQUAL "")
        message(FATAL_ERROR "-- ${PROJECT_NAME}: you are attempting to use vcpkg, but environment variables of `VCPKG_DIR/VCPKG_ROOT` is empty")
    endif()

    # include toolchain
    include("${LIBPRCPP_VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")

    # check vcpkg triplet env. var.
    if(NOT "$ENV{VCPKG_TRIPLET}" STREQUAL "")
        set(LIBPRCPP_VCPKG_TRIPLET "$ENV{VCPKG_TRIPLET}")
    endif()
    if(NOT "$ENV{VCPKG_DEFAULT_TRIPLET}" STREQUAL "")
        set(LIBPRCPP_VCPKG_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}")
    endif()

    # check vcpkg triplet defined var.
    if(NOT "${VCPKG_TRIPLET}" STREQUAL "")
        set(LIBPRCPP_VCPKG_TRIPLET "${VCPKG_TRIPLET}")
    endif()
    if(NOT "${VCPKG_DEFAULT_TRIPLET}" STREQUAL "")
        set(LIBPRCPP_VCPKG_TRIPLET "${VCPKG_DEFAULT_TRIPLET}")
    endif()

    if(LIBPRCPP_VCPKG_TRIPLET STREQUAL "")
       message(FATAL_ERROR "-- ${PROJECT_NAME}: attempt to use vcpkg but triplet is not defined/set, use `-DVCPKG_TRIPLET=processor_type-system_os_name` or `-DVCPKG_DEFAULT_TRIPLET=processor_type-system_os_name` or set those on your environment variable") 
    endif()

    # check and set
    set(LIBPRCPP_VCPKG_INSTALLED_DIR "${LIBPRCPP_VCPKG_DIR}/installed/${LIBPRCPP_VCPKG_TRIPLET}")
    if(EXISTS "${LIBPRCPP_VCPKG_INSTALLED_DIR}")
        # include dirs
        include_directories("${LIBPRCPP_VCPKG_INSTALLED_DIR}/include")
        include_directories("${LIBPRCPP_VCPKG_INSTALLED_DIR}/debug/include")

        # link bin dirs
        link_directories("${LIBPRCPP_VCPKG_INSTALLED_DIR}/bin")
        link_directories("${LIBPRCPP_VCPKG_INSTALLED_DIR}/debug/bin")

        # link lib dirs
        link_directories("${LIBPRCPP_VCPKG_INSTALLED_DIR}/lib")
        link_directories("${LIBPRCPP_VCPKG_INSTALLED_DIR}/debug/lib")

        set(LIBPRCPP_USING_VCPKG true)
    else()
        message(FATAL_ERROR "-- ${PROJECT_NAME}: vpckg error")
    endif()
endif()

## base curl
set(LIBPRCPP_USING_CURL_EXECUTEABLE)

find_file(LIBPRCPP_CURL_EXECUTEABLE "curl")

if(LIBPRCPP_CURL_EXECUTEABLE)
    set(LIBPRCPP_USING_CURL_EXECUTEABLE true)
    message(NOTICE "-- ${PROJECT_NAME}: curl found in ${LIBPRCPP_CURL_EXECUTEABLE}")
endif()

## jsoncpp
set(jsoncpp_FOUND)
set(LIBPRCPP_USING_JSONCPP false)

find_package(jsoncpp CONFIG)

if(jsoncpp_FOUND)
    set(LIBPRCPP_USING_JSONCPP true)
else()
    set(LIBPRCPP_VENDOR_JSONCPP_DIR ${PROJECT_SOURCE_DIR}/vendors/jsoncpp)

    set(JSONCPP_WITH_TESTS false)
    set(JSONCPP_WITH_EXAMPLE false)
    set(JSONCPP_WITH_CMAKE_PACKAGE true)

    add_subdirectory(${LIBPRCPP_VENDOR_JSONCPP_DIR} LIBPRCPP_JSONCPP)

    set(LIBPRCPP_USING_JSONCPP true)
endif()

## nanosvg
set(LIBPRCPP_USING_NANOSVG false)
if(NOT BUILD_SKIPPED_VENDOR_NANOSVG)
    set(LIBPRCPP_VENDOR_NANOSVG_DIR "${PROJECT_SOURCE_DIR}/vendors/nanosvg")

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/out/nanosvg")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/out/nanosvg")
    endif()

    set(LIBPRCPP_VENDOR_NANOSVG_DIR_NANOSVG)

    file(COPY "${LIBPRCPP_VENDOR_NANOSVG_DIR}/src/" DESTINATION "${CMAKE_BINARY_DIR}/out/nanosvg")

    set(LIBPRCPP_VENDOR_NANOSVG_DIR_NANOSVG "${CMAKE_BINARY_DIR}/out")

    include_directories(${LIBPRCPP_VENDOR_NANOSVG_DIR_NANOSVG})

    add_subdirectory(${LIBPRCPP_VENDOR_NANOSVG_DIR} LIBPRCPP_NANOSVG)
    set(LIBPRCPP_USING_NANOSVG true)
endif()

## openssl
set(LIBPRCPP_USING_OPENSSL false)

find_package(OpenSSL CONFIG)
if(OpenSSL_FOUND)
    set(LIBPRCPP_USING_OPENSSL true)
else()
    find_file(LIBPRCPP_OPENSSL_DIR "openssl/evp.h")
    if(LIBPRCPP_OPENSSL_DIR)
        get_filename_component(OpenSSL_DIR "${LIBPRCPP_OPENSSL_DIR}" DIRECTORY)
        
        set(LIBPRCPP_USING_OPENSSL true)
        # include_directories(${OpenSSL_DIR})
    endif()
endif()

## drogon
set(LIBPRCPP_USING_DROGON false)

find_package(Drogon CONFIG)

if(Drogon_FOUND)
    set(LIBPRCPP_USING_DROGON true)
endif()

## cryptopp-cmake
set(LIBPRCPP_USING_CRYPTOPP_CMAKE false)
if(NOT BUILD_SKIPPED_VENDOR_CRYPTOPP_CMAKE)
    set(LIBPRCPP_VENDOR_CRYPTOPP_CMAKE_DIR "${PROJECT_SOURCE_DIR}/vendors/cryptopp-cmake")

    set(CRYPTOPP_BUILD_TESTING false)

    add_subdirectory(${LIBPRCPP_VENDOR_CRYPTOPP_CMAKE_DIR} LIBPRCPP_CRYPTOPP_CMAKE)
    set(LIBPRCPP_USING_CRYPTOPP_CMAKE true)
endif()

## argon2
set(LIBPRCPP_USING_ARGON2 false)

find_file(LIBPRCPP_ARGON2_INCLUDE_DIRS "argon2.h")
if(LIBPRCPP_ARGON2_INCLUDE_DIRS)
    set(LIBPRCPP_USING_ARGON2 true)
endif()

## postgresql
set(LIBPRCPP_USING_POSTGRESQL false)
set(PostgreSQL_FOUND)

find_package(PostgreSQL)

if(PostgreSQL_FOUND)
    set(LIBPRCPP_USING_POSTGRESQL true)
endif()

## scylladb
set(LIBPRCPP_USING_SCYLLADB false)

find_file(LIBPRCPP_SCYLLA_EXECUTEABLE "scylla")
find_file(LIBPRCPP_CASSANDRA_HEADER "cassandra.h")

if(LIBPRCPP_SCYLLA_EXECUTEABLE AND LIBPRCPP_CASSANDRA_HEADER)
    set(LIBPRCPP_USING_SCYLLADB true)
endif()

## libharu
set(LIBPRCPP_USING_LIBHARU false)
if(NOT BUILD_SKIPPED_VENDOR_LIBHARU)
    set(LIBPRCPP_VENDOR_LIBHARU_DIR "${PROJECT_SOURCE_DIR}/vendors/libharu")

    set(LIBPRCPP_VENDOR_LIBHARU_DIR_SOURCE_OUT ${CMAKE_BINARY_DIR}/LIBPRCPP_LIBHARU/src)
    set(LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE_OUT ${CMAKE_BINARY_DIR}/LIBPRCPP_LIBHARU/include)

    set(LIBHPDF_SHARED false)
    set(LIBHPDF_STATIC true)
    set(LIBHPDF_EXAMPLES false)

    include_directories(${LIBPRCPP_VENDOR_LIBHARU_DIR}/include)

    include_directories(${LIBPRCPP_VENDOR_LIBHARU_DIR_SOURCE_OUT})
    include_directories(${LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE_OUT})

    link_directories(AFTER "${LIBPRCPP_VENDOR_LIBHARU_DIR_SOURCE_OUT}")

    add_subdirectory(${LIBPRCPP_VENDOR_LIBHARU_DIR} LIBPRCPP_LIBHARU)

    set(LIBPRCPP_USING_LIBHARU true)
endif()

## stb
set(LIBPRCPP_USING_STB false)
if(NOT BUILD_SKIPPED_VENDOR_STB)
    if(NOT DEFINED ${Stb_INCLUDE_DIR})
        set(Stb_INCLUDE_DIR "")
    endif()

    set(LIBPRCPP_VENDOR_STB_DIR "${PROJECT_SOURCE_DIR}/vendors/stb")

    if(NOT ${LIBPRCPP_VENDOR_STB_DIR} STREQUAL "")
        set(LIBPRCPP_USING_STB true)
        set(Stb_INCLUDE_DIR ${LIBPRCPP_VENDOR_STB_DIR})
        include_directories(${Stb_INCLUDE_DIR})
    endif()

    set(LIBPRCPP_USING_STB true)
endif()

## zxing-cpp
set(LIBPRCPP_USING_ZXING_CPP false)
if(NOT BUILD_SKIPPED_VENDOR_ZXING_CPP)
    set(LIBPRCPP_VENDOR_ZXING_CPP_DIR "${PROJECT_SOURCE_DIR}/vendors/zxing-cpp")

    set(ZXING_EXPERIMENTAL_API true)
    set(ZXING_EXAMPLES false)
    set(ZXING_BLACKBOX_TESTS false)
    set(ZXING_UNIT_TESTS false)

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/out/ZXing")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/out/ZXing")
    endif()

    set(LIBPRCPP_VENDOR_ZXING_CPP_DIR_ZXING)

    file(COPY "${LIBPRCPP_VENDOR_ZXING_CPP_DIR}/core/src/" DESTINATION "${CMAKE_BINARY_DIR}/out/ZXing")

    set(LIBPRCPP_VENDOR_ZXING_CPP_DIR_ZXING_DIR "${CMAKE_BINARY_DIR}/out")

    include_directories(${LIBPRCPP_VENDOR_ZXING_CPP_DIR_ZXING_DIR})

    add_subdirectory(${LIBPRCPP_VENDOR_ZXING_CPP_DIR} LIBPRCPP_ZXING_CPP)
    set(LIBPRCPP_USING_ZXING_CPP true)
endif()

## sdl
set(LIBPRCPP_USING_SDL false)
if(NOT BUILD_SKIPPED_VENDOR_SDL)
    set(LIBPRCPP_VENDOR_SDL_DIR "${PROJECT_SOURCE_DIR}/vendors/sdl")

    include_directories(${LIBPRCPP_VENDOR_SDL_DIR}/include)

    link_directories(AFTER "${CMAKE_BINARY_DIR}/LIBPRCPP_SDL")

    set(SDL_STATIC true)
    set(SDL_TEST_LIBRARY false)

    add_subdirectory(${LIBPRCPP_VENDOR_SDL_DIR} LIBPRCPP_SDL)

    set(LIBPRCPP_USING_SDL true)
endif()


# project library
add_library(${PROJECT_NAME} ${LIBPRCPP_SOURCES_FILES})
# set(LIBPRCPP_BUILD_SHARED_LIBS false)
# if(BUILD_SHARED_LIBS)
#     set_target_properties(${PROJECT_NAME} PROPERTIES
#         VERSION "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}"
#         SOVERSION "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}"
#     )
#     set(LIBPRCPP_BUILD_SHARED_LIBS true)
# endif() # skip for now

## build tools
set(LIBPRCPP_BUILD_TOOLS false)
if(BUILD_TOOLS)
    set(LIBPRCPP_BUILD_TOOLS true)
endif()

## build tests
set(LIBPRCPP_BUILD_TESTS false)
if(BUILD_TESTS)
    set(LIBPRCPP_BUILD_TESTS true)
endif()


# target links
## jsoncpp
if(LIBPRCPP_USING_JSONCPP)
    if(jsoncpp_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp)
    endif()
endif()

## nanosvg
if(LIBPRCPP_USING_NANOSVG)
    target_link_libraries(${PROJECT_NAME} PRIVATE nanosvg nanosvgrast)
endif()

## openssl
if(LIBPRCPP_USING_OPENSSL)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

## drogon
if(LIBPRCPP_USING_DROGON)
    target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
endif()

## cryptopp-cmake
if(LIBPRCPP_USING_CRYPTOPP_CMAKE)
    target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp::cryptopp)
endif()

## argon2
if(LIBPRCPP_USING_ARGON2)
    target_link_libraries(${PROJECT_NAME} PRIVATE argon2)
endif()

## postgresql
if(LIBPRCPP_USING_POSTGRESQL)
    if(PostgreSQL_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)
    endif()
endif()

## scylladb
if(LIBPRCPP_USING_SCYLLADB)
    target_link_libraries(${PROJECT_NAME} PRIVATE scylla-cpp-driver)
endif()

## libharu
if(LIBPRCPP_USING_LIBHARU)
    target_link_libraries(${PROJECT_NAME} PRIVATE hpdf)

    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE})
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBPRCPP_VENDOR_LIBHARU_DIR_INCLUDE_OUT})
endif()

## stb
if(LIBPRCPP_USING_STB)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
endif()

## zxing-cpp
if(LIBPRCPP_USING_ZXING_CPP)
    target_link_libraries(${PROJECT_NAME} PRIVATE ZXing::Core ZXing::ZXing)
endif()

## sdl
if(LIBPRCPP_USING_SDL)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3-static SDL_uclibc SDL3_Headers)
endif()


# # install options
# ## skip for now
# if(NOT WIN32)
#     include(GNUInstallDirs)
# endif()
# ## target
# install(TARGETS ${PROJECT_NAME}
#         EXPORT LibprcppTargets
#         ARCHIVE DESTINATION lib
#         LIBRARY DESTINATION lib
#         RUNTIME DESTINATION bin)

# ## target share
# install(EXPORT LibprcppTargets
#         FILE LibprcppConfig.cmake
#         # NAMESPACE libprcpp::
#         DESTINATION share/libprcpp)

# ## target headers
# install(FILES ${LIBPRCPP_HEADERS_FILES_BASE} DESTINATION include/libprcpp)
# install(FILES ${LIBPRCPP_HEADERS_FILES_CONSTANTS} DESTINATION include/libprcpp/constants)
# install(FILES ${LIBPRCPP_HEADERS_FILES_ENUMS} DESTINATION include/libprcpp/enums)
# install(FILES ${LIBPRCPP_HEADERS_FILES_FUNCTIONS} DESTINATION include/libprcpp/functions)
# install(FILES ${LIBPRCPP_HEADERS_FILES_INTERFACES} DESTINATION include/libprcpp/interfaces)
# install(FILES ${LIBPRCPP_HEADERS_FILES_TYPES} DESTINATION include/libprcpp/types)


# force naming
set(PREFIX                      "")
set(IMPORT_PREFIX               "")
set(OUTPUT_NAME                 "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")


# compiler options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(LIBPRCPP_COMPILER_ID    1)
    set(LIBPRCPP_COMPILER_GNU   true)
    set(LIBPRCPP_COMPILER_MSVC  false)
    set(LIBPRCPP_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-value
        -Wno-unused-variable
        -Wno-reorder
        -Wno-parentheses
        -Wno-switch
        -Wno-format
        -Wno-invalid-offsetof
        -Wno-multichar
        -Wno-char-subscripts
        -Wno-empty-body
        -Wno-unused-function
        -Wno-deprecated-declarations
        -lm
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(LIBPRCPP_COMPILER_ID    2)
    set(LIBPRCPP_COMPILER_GNU   false)
    set(LIBPRCPP_COMPILER_MSVC  true)
    set(LIBPRCPP_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /wd4996
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(LIBPRCPP_COMPILER_ID    3)
    set(LIBPRCPP_COMPILER_GNU   false)
    set(LIBPRCPP_COMPILER_MSVC  false)
    set(LIBPRCPP_COMPILER_CLANG true)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-value
        -Wno-unused-variable
        -Wno-reorder
        -Wno-parentheses
        -Wno-switch
        -Wno-format
        -Wno-dynamic-class-memaccess
        -Wno-unused-private-field
        -Wno-invalid-offsetof
        -Wno-multichar
        -Wno-char-subscripts
        -Wno-null-conversion
        -Wno-empty-body
        -Wno-unused-lambda-capture
        -Wno-unused-function
        -Wno-tautological-constant-out-of-range-compare
        -Wno-deprecated-declarations
    )
else()
    set(LIBPRCPP_COMPILER_ID    0)
    set(LIBPRCPP_COMPILER_GNU   false)
    set(LIBPRCPP_COMPILER_MSVC  false)
    set(LIBPRCPP_COMPILER_CLANG false)

    message(NOTICE "-- ${PROJECT_NAME}: -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
endif()

## warning
if(CMAKE_CXX_FLAGS STREQUAL "")
    message(WARNING "-- ${PROJECT_NAME} cxx flags is empty")
endif()


# libprcpp config
configure_file(
    ${PROJECT_SOURCE_DIR}/library/inc/libprcpp/config.in.hh
    ${PROJECT_SOURCE_DIR}/library/inc/libprcpp/config.hh
)

# libprcpp export
generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/library/inc/libprcpp/export.hh
)


# target include
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/library/inc
)


# aux source dir
## N/A

# target source
## dont expand this yet
target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/library/src/libprcpp
)


# extra subdir
## tests
if(BUILD_TESTS)
    add_subdirectory(test/test_libprcpp)
endif()

## tools
if(BUILD_TOOLS)
    add_subdirectory(tools/prgent)
endif()


# post build
## TBA


# final configuration log
message(NOTICE "-- ${PROJECT_NAME} ${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}")
message(NOTICE "   system               : ${LIBPRCPP_SYSTEM_NAME}")
message(NOTICE "   compiler             : ${CMAKE_CXX_COMPILER_ID}")
message(NOTICE "   processor            : ${LIBPRCPP_SYSTEM_PROCESSOR_OUT}")
message(NOTICE "   build type           : ${LIBPRCPP_SYSTEM_BUILD_TYPE}")
message(NOTICE "   build tests          : ${LIBPRCPP_BUILD_TESTS}")
message(NOTICE "   build tools          : ${LIBPRCPP_BUILD_TOOLS}")
# message(NOTICE "   build shared lib     : ${LIBPRCPP_BUILD_SHARED_LIBS}") # skip for now
message(NOTICE "   build using vcpkg    : ${LIBPRCPP_USING_VCPKG}")
message(NOTICE "   cmake cxx std        : ${CMAKE_CXX_STANDARD}")
message(NOTICE "   cmake cxx flags      : ${CMAKE_CXX_FLAGS}")
message(NOTICE "   ======================================================")
message(NOTICE "   using sdl            : ${LIBPRCPP_USING_SDL}")
message(NOTICE "   using stb            : ${LIBPRCPP_USING_STB}")
message(NOTICE "   using argon2         : ${LIBPRCPP_USING_ARGON2}")
message(NOTICE "   using drogon         : ${LIBPRCPP_USING_DROGON}")
message(NOTICE "   using jsoncpp        : ${LIBPRCPP_USING_JSONCPP}")
message(NOTICE "   using nanosvg        : ${LIBPRCPP_USING_NANOSVG}")
message(NOTICE "   using openssl        : ${LIBPRCPP_USING_OPENSSL}")
message(NOTICE "   using scylladb       : ${LIBPRCPP_USING_SCYLLADB}")
message(NOTICE "   using zxing-cpp      : ${LIBPRCPP_USING_ZXING_CPP}")
message(NOTICE "   using postgresql     : ${LIBPRCPP_USING_POSTGRESQL}")
message(NOTICE "   using libharu/hpdf   : ${LIBPRCPP_USING_LIBHARU}")
message(NOTICE "   using cryptopp-cmake : ${LIBPRCPP_USING_CRYPTOPP_CMAKE}")
message(NOTICE "   ======================================================")
message(NOTICE "   executeable curl     : ${LIBPRCPP_USING_CURL_EXECUTEABLE} -> ${LIBPRCPP_CURL_EXECUTEABLE}")
