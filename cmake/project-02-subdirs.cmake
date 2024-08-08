# RESERVED: vendors

# project
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libprcpp)

if(PROJECT_BUILD_TEST)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_cryptography)
endif()
