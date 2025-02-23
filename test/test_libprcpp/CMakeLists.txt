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
if(NOT MSVC)
    target_link_libraries(test_libprcpp_cryptography PRIVATE -lm)

    if(LIBPRCPP_COMPILER_GNU) # error gnu gcc 12.2
        target_link_libraries(test_libprcpp_cryptography PRIVATE -lm) # stil error here
        if(EXISTS "/usr/lib/x86_64-linux-gnu/libm.so")
            target_link_libraries(test_libprcpp_cryptography PRIVATE "/usr/lib/x86_64-linux-gnu/libm.so") # somehow build not error
        else()
            message(WARNING "test_libprcpp_cryptography for gcc has error, be warn")
        endif()
    endif()
endif()

add_executable(test_libprcpp_file_enc_dec test_libprcpp_file_enc_dec.cc)
target_link_libraries(test_libprcpp_file_enc_dec PRIVATE libprcpp)
if(NOT MSVC)
    target_link_libraries(test_libprcpp_file_enc_dec PRIVATE -lm)

    if(LIBPRCPP_COMPILER_GNU) # error gnu gcc 12.2
        target_link_libraries(test_libprcpp_file_enc_dec PRIVATE -lm) # somehow build not error
    endif()
endif()


# name: test_libprcpp_barcode_qrcode
# required libs:
# - stb
# - nanosvg
# - zxing-cpp
add_executable(test_libprcpp_barcode_qrcode test_libprcpp_barcode_qrcode.cc)
target_link_libraries(test_libprcpp_barcode_qrcode PRIVATE libprcpp)
if(NOT MSVC)
    target_link_libraries(test_libprcpp_barcode_qrcode PRIVATE -lm)

    if(LIBPRCPP_COMPILER_GNU) # error gnu gcc 12.2
        target_link_libraries(test_libprcpp_barcode_qrcode PRIVATE -lm) # somehow build not error
    endif()
endif()


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
if(LIBPRCPP_USING_SCYLLADB)
    add_executable(test_libprcpp_scylladb test_libprcpp_scylladb.cc)
    target_link_libraries(test_libprcpp_scylladb PRIVATE libprcpp)
endif()


# name: test_libprcpp_pdf_maker
# required libs:
# - jsoncpp
# - libharu
# error:
# - gnu gcc compiler
add_executable(test_libprcpp_pdf_maker test_libprcpp_pdf_maker.cc)
target_link_libraries(test_libprcpp_pdf_maker PRIVATE libprcpp)
if(NOT MSVC)
    target_link_libraries(test_libprcpp_pdf_maker PRIVATE -lm)

    if(LIBPRCPP_COMPILER_GNU) # error gnu gcc 12.2
        target_link_libraries(test_libprcpp_pdf_maker PRIVATE -lm) # stil error here
        if(EXISTS "/usr/lib/x86_64-linux-gnu/libm.so")
            target_link_libraries(test_libprcpp_pdf_maker PRIVATE "/usr/lib/x86_64-linux-gnu/libm.so") # somehow build not error
        else()
            message(WARNING "test_libprcpp_pdf_maker for gcc has error, be warn")
        endif()
    endif()
endif()


# name: test_libprcpp_sdl3_native_resolution
# required libs:
# - sdl3
add_executable(test_libprcpp_sdl3_native_resolution test_libprcpp_sdl3_native_resolution.cc)
target_link_libraries(test_libprcpp_sdl3_native_resolution PRIVATE libprcpp)


# #
# foreach(linked qwe asd zxc)
#     # 
# endforeach()

