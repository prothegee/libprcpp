if(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK)
cmake_minimum_required(VERSION 3.15...3.30)
project(test_scylladb_drogon)

add_executable(${PROJECT_NAME}
    test_scylladb_drogon.cc
)

set(PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(LIBPRCPP_BUILD_COMPILER_ID 1)

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
    set(LIBPRCPP_BUILD_COMPILER_ID 2)

    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(LIBPRCPP_BUILD_COMPILER_ID 3)

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

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE libprcpp)

aux_source_directory(plugins TEST_SCYLLADB_DROGON_DIR_PLUGINS)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${TEST_SCYLLADB_DROGON_DIR_PLUGINS}
)
endif()
