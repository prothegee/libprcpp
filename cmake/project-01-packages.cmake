# jsoncpp
set(LIBPRCPP_PROJECT_USING_JSONCPP false)

find_package(jsoncpp CONFIG)
if(jsoncpp_FOUND)
    set(LIBPRCPP_PROJECT_USING_JSONCPP true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package not found, try find path")

    find_path(LIBPRCPP_JSONCPP_INCLUDE_DIR "json/")
    if(LIBPRCPP_JSONCPP_INCLUDE_DIR)
        set(LIBPRCPP_PROJECT_USING_JSONCPP true)
        message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp path found in ${LIBPRCPP_JSONCPP_INCLUDE_DIR}")
    endif()
endif()


# openssl
set(LIBPRCPP_PROJECT_USING_OPENSSL false)

find_package(OpenSSL CONFIG)
if(OpenSSL_FOUND)
    set(LIBPRCPP_PROJECT_USING_OPENSSL true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package not found, try find path")

    find_path(LIBPRCPP_OPENSSL_INCLUDE_DIRS "openssl/")
    if(LIBPRCPP_OPENSSL_INCLUDE_DIRS)
        set(LIBPRCPP_PROJECT_USING_OPENSSL true)
        message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL path found as path in ${LIBPRCPP_OPENSSL_INCLUDE_DIRS}")
    endif()
endif()


# drogon framework
set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK false)

find_package(Drogon CONFIG)
if(Drogon_FOUND)
    set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   Drogon Framework package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   Drogon Framework package not found")
endif()


# cryptopp-cmake
set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE false)

find_package(cryptopp CONFIG)
if(cryptopp_FOUND)
    set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   cryptopp-cmake package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   cryptopp-cmake package not found")
endif()


# argon2
set(LIBPRCPP_PROJECT_USING_ARGON false)

find_file(LIBPRCPP_ARGON2_INCLUDE_DIRS "include/argon2.h") # unix only, not sure in windows for now
if(LIBPRCPP_ARGON2_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_ARGON true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   argon.h found in ${LIBPRCPP_ARGON2_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   argon.h not found")
endif()


# scylladb *but somehow cassandra
set(LIBPRCPP_PROJECT_USING_SCYLLADB false)

find_file(LIBPRCPP_CASS_CPP_INCLUDE_DIRS "cassandra.h")
if(LIBPRCPP_CASS_CPP_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_SCYLLADB true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   cassandra.h found in ${LIBPRCPP_CASS_CPP_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   cassandra.h not found")
endif()


# jwt-cpp
set(LIBPRCPP_PROJECT_USING_JWT_CPP false)

find_file(LIBPRCPP_JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h")
if(LIBPRCPP_JWT_CPP_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_JWT_CPP true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   jwt-cpp header found in ${LIBPRCPP_JWT_CPP_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   jwt-cpp header not found")
endif()


# libharu
set(LIBPRCPP_PROJECT_USING_LIBHARU false)

find_file(LIBPRCPP_LIBHARU_INCLUDE_DIRS "hpdf.h")
if(LIBPRCPP_LIBHARU_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_LIBHARU true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   libharu header found in ${LIBPRCPP_LIBHARU_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   libharu header not found")
endif()
