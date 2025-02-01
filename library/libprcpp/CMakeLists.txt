cmake_minimum_required(VERSION 3.15...3.30)


set(LIBPRCPP_VERSION_MAJOR 0)
set(LIBPRCPP_VERSION_MINOR 15)
set(LIBPRCPP_VERSION_PATCH 0)
set(LIBPRCPP_VERSION_DATES 20250201)
set(LIBPRCPP_VERSION_STRING "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}.${LIBPRCPP_VERSION_DATES}")


# actual libprcpp project dir
set(LIBPRCPP_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


include(CheckIncludeFileCXX)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(FindPackageHandleStandardArgs)
include(cmake/libprcpp-config.cmake)
include(cmake/libprcpp-files_headers.cmake)
include(cmake/libprcpp-files_sources.cmake)
include(cmake/libprcpp-post_build.cmake)


# core project
project(libprcpp)

set(LIBPRCPP_PROJECT "libprcpp")
set(LIBPRCPP_IS_SHARED false)


add_library(${LIBPRCPP_PROJECT})
if(BUILD_SHARED_LIBS)
    set_target_properties(${LIBPRCPP_PROJECT} PROPERTIES
        VERSION "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}"
        SOVERSION "${LIBPRCPP_VERSION_MAJOR}.${LIBPRCPP_VERSION_MINOR}.${LIBPRCPP_VERSION_PATCH}"
    )
    set(LIBPRCPP_IS_SHARED true)
endif()


include(cmake/libprcpp-install.cmake)


set(PREFIX        "")
set(IMPORT_PREFIX "")
set(OUTPUT_NAME "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")


if(LIBPRCPP_COMPILER_GNU) # gnu compiler
    target_compile_options(${LIBPRCPP_PROJECT} PRIVATE
        -Wno-unused-value
        -Wno-unused-variable
    )
elseif(LIBPRCPP_COMPILER_MSVC) # msvc compiler
    if(NOT CMAKE_CXX_FLAGS MATCHES "/EHsc")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
    endif()

    target_compile_options(${LIBPRCPP_PROJECT} PRIVATE
        /W4
    )
elseif(LIBPRCPP_COMPILER_CLANG) # clang compiler
    target_compile_options(${LIBPRCPP_PROJECT} PRIVATE
        -Wno-unused-value
        -Wno-unused-variable
    )
else() # undefined
    message(WARNING "-- ${LIBPRCPP_PROJECT}:\n   cmake compiler id of ${CMAKE_CXX_COMPILER_ID} is not configured / not supported")           
endif()


include(cmake/libprcpp-target_link_libs.cmake)


# libprcpp export header
generate_export_header(${LIBPRCPP_PROJECT}
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/inc/libprcpp/base/export.hh
)


# libprcpp config
configure_file(
    ${PROJECT_SOURCE_DIR}/config.in.hh
    ${PROJECT_SOURCE_DIR}/inc/libprcpp/base/config.hh
)


# aux source to target source
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp            LIBPRCPP_DIR)
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp/base       LIBPRCPP_DIR_BASE)
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp/constants  LIBPRCPP_DIR_CONSTANTS)
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp/enums      LIBPRCPP_DIR_ENUMS)
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp/functions  LIBPRCPP_DIR_FUNCTIONS)
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp/interfaces LIBPRCPP_DIR_INTERFACES)
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp/modules    LIBPRCPP_DIR_MODULES)
aux_source_directory(${LIBPRCPP_PROJECT_DIR}/src/libprcpp/types      LIBPRCPP_DIR_TYPES)

target_sources(${LIBPRCPP_PROJECT}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LIBPRCPP_DIR}
        ${LIBPRCPP_DIR_BASE}
        ${LIBPRCPP_DIR_CONSTANTS}
        ${LIBPRCPP_DIR_ENUMS}
        ${LIBPRCPP_DIR_FUNCTIONS}
        ${LIBPRCPP_DIR_INTERFACES}
        ${LIBPRCPP_DIR_MODULES}
        ${LIBPRCPP_DIR_TYPES}
)


# target include
target_include_directories(${LIBPRCPP_PROJECT}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/inc
        $<INSTALL_INTERFACE:${INSTALL_INCLUDE_DIR}>
)


# supply last log cxx flags and linker flags
if(NOT CMAKE_CXX_FLAGS STREQUAL "")
    message(NOTICE "-- ${LIBPRCPP_PROJECT}: CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()
if(NOT CMAKE_EXE_LINKER_FLAGS STREQUAL "")
    message(NOTICE "-- ${LIBPRCPP_PROJECT}: CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
endif()


# supply last log configuration
message(NOTICE "-- ${LIBPRCPP_PROJECT} v${LIBPRCPP_VERSION_STRING} for ${LIBPRCPP_SYSTEM_BUILD_TYPE} using c++${CMAKE_CXX_STANDARD} configured")
