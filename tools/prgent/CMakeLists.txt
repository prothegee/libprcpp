cmake_minimum_required(VERSION 3.15...3.30)
project(prgent LANGUAGES CXX)

set(PRGENT_VERSION_MAJOR 0)
set(PRGENT_VERSION_MINOR 0)
set(PRGENT_VERSION_PATCH 0)
set(PRGENT_VERSION_DATES 20250121)
set(PRGENT_VERSION_STRING "${PRGENT_VERSION_MAJOR}.${PRGENT_VERSION_MINOR}.${PRGENT_VERSION_PATCH}.${PRGENT_VERSION_DATES}")

# 0: executeable
# 1: static lib
# 2: shared lib
set(PRGENT_TARGET_MODE)

set(PRGENT_AS_LIB true)

include(CheckIncludeFileCXX)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(FindPackageHandleStandardArgs)

if(PRGENT_TARGET_MODE EQUAL 1)
    add_library(${PROJECT_NAME} STATIC src/prgent/prgent.hh src/prgent/prgent.cc)
    message(NOTICE "-- ${PROJECT_NAME} tool:\n   build as static lib v${PRGENT_VERSION_STRING}")
elseif(PRGENT_TARGET_MODE EQUAL 2)
    add_library(${PROJECT_NAME} SHARED src/prgent/prgent.hh src/prgent/prgent.cc)
    message(NOTICE "-- ${PROJECT_NAME} tool:\n   build as shared lib v${PRGENT_VERSION_STRING}")
else()
    add_executable(${PROJECT_NAME} main.cc)
    set(PRGENT_AS_LIB false)
    message(NOTICE "-- ${PROJECT_NAME} tool:\n   build as executeable v${PRGENT_VERSION_STRING}")
endif()

if(PRGENT_AS_LIB)
    set(PREFIX        "lib")
    set(IMPORT_PREFIX "lib")
    set(CMAKE_STATIC_LIBRARY_PREFIX "lib")
    set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PRGENT_COMPILER_GNU   true)
    set(PRGENT_COMPILER_MSVC  false)
    set(PRGENT_COMPILER_CLANG false)

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
    set(PRGENT_COMPILER_GNU   false)
    set(PRGENT_COMPILER_MSVC  true)
    set(PRGENT_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(PRGENT_COMPILER_GNU   false)
    set(PRGENT_COMPILER_MSVC  false)
    set(PRGENT_COMPILER_CLANG true)

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

target_link_libraries(${PROJECT_NAME} PRIVATE libprcpp)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/prgent/base/config.in.hh
    ${PROJECT_SOURCE_DIR}/src/prgent/base/config.hh
)

aux_source_directory(src/prgent             PRGENT_DIR)
aux_source_directory(src/prgent/base        PRGENT_DIR_BASE)
aux_source_directory(src/prgent/constants   PRGENT_DIR_CONSTANTS)
aux_source_directory(src/prgent/enums       PRGENT_DIR_ENUMS)
aux_source_directory(src/prgent/functions   PRGENT_DIR_FUNCTIONS)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PRGENT_DIR}
        ${PRGENT_DIR_BASE}
        ${PRGENT_DIR_CONSTANTS}
        ${PRGENT_DIR_ENUMS}
        ${PRGENT_DIR_FUNCTIONS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/src
)
