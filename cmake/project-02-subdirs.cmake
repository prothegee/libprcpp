# RESERVED: vendors

# project
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libprcpp)

if(LIBPRCPP_PROJECT_BUILD_TEST)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_cryptography)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_csv_rw)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_file_encdec)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_generate_pdf)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_scylladb_drogon)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_scylladb_uuidv4_nochecking)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/test_smtps)
endif()
