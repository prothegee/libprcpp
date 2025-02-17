cmake_minimum_required(VERSION 3.15...3.30)


set(PRGENT_VERSION_MAJOR 0)
set(PRGENT_VERSION_MINOR 10)
set(PRGENT_VERSION_PATCH 0)
set(PRGENT_VERSION_DATES 20250217)
set(PRGENT_VERSION_STRING "${PRGENT_VERSION_MAJOR}.${PRGENT_VERSION_MINOR}.${PRGENT_VERSION_PATCH}.${PRGENT_VERSION_DATES}")


project(prgent)


include(CheckIncludeFileCXX)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(FindPackageHandleStandardArgs)


add_executable(${PROJECT_NAME} inc/prgent/main.hh src/prgent/main.cc)


# # install
# ## skip for now
# install(TARGETS ${PROJECT_NAME}
#         RUNTIME DESTINATION bin)


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
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
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
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
if(NOT MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE -lm)

    if(LIBPRCPP_COMPILER_GNU) # error gnu gcc 12.2
        target_link_libraries(${PROJECT_NAME} PRIVATE -lm) # somehow build not error
    endif()
endif()


aux_source_directory(src/prgent             PRGENT_DIR)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${PRGENT_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/inc
)
