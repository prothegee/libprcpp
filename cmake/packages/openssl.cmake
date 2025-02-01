#[=[
openssl

standard operating system thread library
#]=]
set(LIBPRCPP_PROJECT_USING_OPENSSL false)

find_package(OpenSSL CONFIG)
if(OpenSSL_FOUND)
    set(LIBPRCPP_PROJECT_USING_OPENSSL true)
    message(NOTICE "-- openssl package found")
else()
    message(NOTICE "-- openssl package not found")
    message(NOTICE "-- openssl attempt #1 search")

    find_file(LIBPRCPP_OPENSSL_DIR "openssl/evp.h")
    if(LIBPRCPP_OPENSSL_DIR)
        get_filename_component(OpenSSL_DIR "${LIBPRCPP_OPENSSL_DIR}" DIRECTORY)
        
        set(LIBPRCPP_PROJECT_USING_OPENSSL true)
        include_directories(${OpenSSL_DIR})
        message(NOTICE "-- openssl found in ${OpenSSL_DIR}")
    else()
        message(NOTICE "-- openssl still not found")
    endif()
endif()
