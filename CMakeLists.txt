cmake_minimum_required(VERSION 3.15...3.30)
project(libprcpp LANGUAGES CXX)

include(CheckIncludeFileCXX)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(FindPackageHandleStandardArgs)
include(cmake/project-00-lib.cmake)
include(cmake/project-01-config.cmake)
include(cmake/project-02-post_build.cmake)

set(PREFIX        "")
set(IMPORT_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(LIBPRCPP_PROJECT_BUILD_SHARED_LIB)
    add_library(${PROJECT_NAME} SHARED
        src/libprcpp/libprcpp.hh
        src/libprcpp/libprcpp.cc
    )
else()
    add_library(${PROJECT_NAME}
        src/libprcpp/libprcpp.hh
        src/libprcpp/libprcpp.cc
    )
endif()


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(LIBPRCPP_BUILD_COMPILER_ID 1)

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
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(LIBPRCPP_BUILD_COMPILER_ID 2)

    set(LIBPRCPP_COMPILER_GNU   false)
    set(LIBPRCPP_COMPILER_MSVC  true)
    set(LIBPRCPP_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(LIBPRCPP_BUILD_COMPILER_ID 3)

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
    )
else()
    message(WARNING "-- ${PROJECT_NAME}:\n   -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
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

    # drogon_create_views(${PROJECT_NAME}
    #     ${CMAKE_CURRENT_SOURCE_DIR}/src/libprcpp/views
    #     ${EXECUTABLE_OUTPUT_PATH}
    # )
else()
    set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK false)
endif()

if(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE)
    set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE true)
    target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp::cryptopp)
else()
    set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE false)
endif()

if(LIBPRCPP_PROJECT_USING_ARGON2)
    set(LIBPRCPP_PROJECT_USING_ARGON2 true)
    target_link_libraries(${PROJECT_NAME} PRIVATE argon2)
else()
    set(LIBPRCPP_PROJECT_USING_ARGON2 false)
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

if(LIBPRCPP_PROJECT_USING_LIBQRENCODE)
    set(LIBPRCPP_PROJECT_USING_LIBQRENCODE true)
    if(LIBPRCPP_PROJECT_USING_LIBQRENCODE_DEFAULT)
        target_include_directories(${PROJECT_NAME} PRIVATE ${QRENCODE_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME} PRIVATE qrencode)
    else()
        target_include_directories(${PROJECT_NAME} PRIVATE ${QRENCODE_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${QRENCODE_LIBRARIES})
    endif()
else()
    set(LIBPRCPP_PROJECT_USING_LIBQRENCODE false)
endif()

if(LIBPRCPP_PROJECT_USING_ZXING)
    set(LIBPRCPP_PROJECT_USING_ZXING true)
    target_link_libraries(${PROJECT_NAME} PRIVATE ZXing::Core ZXing::ZXing)
else()
    set(LIBPRCPP_PROJECT_USING_ZXING false)
endif()

generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/src/libprcpp/base/export.hh
)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/libprcpp/base/config.in.hh
    ${PROJECT_SOURCE_DIR}/src/libprcpp/base/config.hh
)

aux_source_directory(src/libprcpp            LIBPRCPP_DIR)
aux_source_directory(src/libprcpp/base       LIBPRCPP_DIR_BASE)
aux_source_directory(src/libprcpp/constants  LIBPRCPP_DIR_CONSTANTS)
aux_source_directory(src/libprcpp/enums      LIBPRCPP_DIR_ENUMS)
aux_source_directory(src/libprcpp/interfaces LIBPRCPP_DIR_INTERFACES)
aux_source_directory(src/libprcpp/modules    LIBPRCPP_DIR_MODULES)
aux_source_directory(src/libprcpp/types      LIBPRCPP_DIR_TYPES)

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

if(LIBPRCPP_PROJECT_BUILD_TEST)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_cryptography)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_csv_rw)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_date_and_time)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_file_encdec)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_generate_pdf)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_parser_json)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_scylladb_drogon)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_scylladb_uuidv4_nochecking)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_smtps)
endif()

if(LIBPRCPP_PROJECT_BUILD_TOOL)
    # RESERVED
endif()

