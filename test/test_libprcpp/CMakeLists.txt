cmake_minimum_required(VERSION 3.15...3.30)


project(test_libprcpp)


include(CheckIncludeFileCXX)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(FindPackageHandleStandardArgs)


# name: test_libprcpp_date_and_times
# required libs:
# - n/a
add_executable(test_libprcpp_date_and_times test_libprcpp_date_and_times.cc)
target_link_libraries(test_libprcpp_date_and_times PRIVATE libprcpp)


# name: test_libprcpp_parser_json
# required libs:
# - jsoncpp
add_executable(test_libprcpp_parser_json test_libprcpp_parser_json.cc)
target_link_libraries(test_libprcpp_parser_json PRIVATE libprcpp)


# name:
# - test_libprcpp_cryptography
# - test_libprcpp_file_enc_dec
# required libs:
# - argon2
# - openssl
# - cryptopp-cmake
add_executable(test_libprcpp_cryptography test_libprcpp_cryptography.cc)
target_link_libraries(test_libprcpp_cryptography PRIVATE libprcpp)

add_executable(test_libprcpp_file_enc_dec test_libprcpp_file_enc_dec.cc)
target_link_libraries(test_libprcpp_file_enc_dec PRIVATE libprcpp)


# name: test_libprcpp_barcode_qrcode
# required libs:
# - stb
# - nanosvg
# - zxing-cpp
add_executable(test_libprcpp_barcode_qrcode test_libprcpp_barcode_qrcode.cc)
target_link_libraries(test_libprcpp_barcode_qrcode PRIVATE libprcpp)


# name: test_libprcpp_smtps_curl
# required libs:
# - jsoncpp
# required executeable:
# - curl
# required config file: test_libprcpp_smtps_curl.json (you can copy test_libprcpp_smtps_curl.debug.json and rename to test_libprcpp_smtps_curl.json first)
if(LIBPRCPP_FOUND_CURL)
    add_executable(test_libprcpp_smtps_curl test_libprcpp_smtps_curl.cc)
    target_link_libraries(test_libprcpp_smtps_curl PRIVATE libprcpp)
endif()


# name: test_libprcpp_scylladb
# required libs:
# - jsoncpp
# - scylla-cpp-driver
# required config file: test_libprcpp_scylladb.json (you can copy test_libprcpp_scylladb.debug.json and rename to test_libprcpp_scylladb.json first)
if(LIBPRCPP_PROJECT_USING_SCYLLADB)
    add_executable(test_libprcpp_scylladb test_libprcpp_scylladb.cc)
    target_link_libraries(test_libprcpp_scylladb PRIVATE libprcpp)
endif()


# name: test_libprcpp_pdf_maker
# required libs:
# - jsoncpp
# - libharu
add_executable(test_libprcpp_pdf_maker test_libprcpp_pdf_maker.cc)
target_link_libraries(test_libprcpp_pdf_maker PRIVATE libprcpp)
