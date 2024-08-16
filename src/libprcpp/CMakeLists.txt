cmake_minimum_required(VERSION 3.15...3.30)
project(libprcpp)

set(LIBPRCPP_VERSION_MAJOR 0)
set(LIBPRCPP_VERSION_MINOR 3)
set(LIBPRCPP_VERSION_PATCH 0)
set(LIBPRCPP_VERSION_DATES 20240816)
set(LIBPRCPP_VERSION_STRING "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}.${LIBPRCPP_VERSION_DATES}")

message(STATUS "${PROJECT_NAME} version:\n   ${LIBPRCPP_VERSION_STRING}")

add_library(${PROJECT_NAME}
    src/libprcpp/libprcpp.h
    src/libprcpp/libprcpp.cc
)

set(PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_BUILD_COMPILER_ID 1)

    target_compile_options(${PROJECT_NAME} PRIVATE
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
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(PROJECT_BUILD_COMPILER_ID 2)

    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(PROJECT_BUILD_COMPILER_ID 3)

    target_compile_options(${PROJECT_NAME} PRIVATE
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
    )
else()
    message(FATAL_ERROR "-DCMAKE_CXX_COMPILER_ID is not recognized")
endif()

if(LIBPRCPP_PROJECT_USING_JSONCPP)
    set(LIBPRCPP_PROJECT_USING_JSONCPP true)
    target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)
else()
    set(LIBPRCPP_PROJECT_USING_JSONCPP false)
endif()

if(LIBPRCPP_PROJECT_USING_OPENSSL)
    set(LIBPRCPP_PROJECT_USING_OPENSSL true)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)
else()
    set(LIBPRCPP_PROJECT_USING_OPENSSL false)
endif()

if(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK)
    set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK true)
    target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

    drogon_create_views(${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libprcpp/views
        ${EXECUTABLE_OUTPUT_PATH}
    )
else()
    set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK false)
endif()

if(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE)
    set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE true)
    target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp::cryptopp)
else()
    set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE false)
endif()

if(LIBPRCPP_PROJECT_USING_SCYLLADB)
    set(LIBPRCPP_PROJECT_USING_SCYLLADB true)
    target_link_libraries(${PROJECT_NAME} PRIVATE scylla-cpp-driver)
else()
    set(LIBPRCPP_PROJECT_USING_SCYLLADB false)
endif()

if(LIBPRCPP_PROJECT_USING_JWT_CPP)
    set(LIBPRCPP_PROJECT_USING_JWT_CPP true)
else()
    set(LIBPRCPP_PROJECT_USING_JWT_CPP false)
endif()

if(LIBPRCPP_PROJECT_USING_LIBHARU)
    set(LIBPRCPP_PROJECT_USING_LIBHARU true)
    target_link_libraries(${PROJECT_NAME} PRIVATE hpdf)
else()
    set(LIBPRCPP_PROJECT_USING_LIBHARU false)
endif()

set(PROJECT_CPP_STANDARD ${CMAKE_CXX_STANDARD})

include(GenerateExportHeader)

generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/src/libprcpp/base/export.h
)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/libprcpp/base/config.in.h
    ${PROJECT_SOURCE_DIR}/src/libprcpp/base/config.h
)

aux_source_directory(src/libprcpp LIBPRCPP_DIR)
aux_source_directory(src/libprcpp/base LIBPRCPP_DIR_BASE)
aux_source_directory(src/libprcpp/constants LIBPRCPP_DIR_CONSTANTS)
aux_source_directory(src/libprcpp/enums LIBPRCPP_DIR_ENUMS)
aux_source_directory(src/libprcpp/interfaces LIBPRCPP_DIR_INTERFACES)
aux_source_directory(src/libprcpp/modules LIBPRCPP_DIR_MODULES)
aux_source_directory(src/libprcpp/types LIBPRCPP_DIR_TYPES)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LIBPRCPP_DIR}
        ${LIBPRCPP_DIR_BASE}
        ${LIBPRCPP_DIR_CONSTANTS}
        ${LIBPRCPP_DIR_ENUMS}
        ${LIBPRCPP_DIR_INTERFACES}
        ${LIBPRCPP_DIR_MODULES}
        ${LIBPRCPP_DIR_TYPES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/src
)
