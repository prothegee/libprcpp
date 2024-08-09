# jsoncpp
set(LIBPRCPP_PROJECT_USING_JSONCPP false)

find_package(jsoncpp CONFIG)
if(jsoncpp_FOUND)
    set(LIBPRCPP_PROJECT_USING_JSONCPP true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package not found")
endif()


# openssl
set(LIBPRCPP_PROJECT_USING_OPENSSL false)

find_file(OPENSSL_INCLUDE_DIRS "openssl")
if(OPENSSL_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_OPENSSL true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package not found")
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


# scylladb *but somehow cassandra
set(LIBPRCPP_PROJECT_USING_SCYLLADB false)

find_path(CASS_CPP_INCLUDE_DIRS "cassandra.h")
if(CASS_CPP_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_SCYLLADB true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   cassandra.h found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   cassandra.h not found")
endif()


# jwt-cpp
set(LIBPRCPP_PROJECT_USING_JWT_CPP false)

find_path(JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h")
if(JWT_CPP_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_JWT_CPP true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   jwt-cpp package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   jwt-cpp package not found")
endif()

# libharu
set(LIBPRCPP_PROJECT_USING_LIBHARU false)
find_path(LIBHARU_INCLUDE_DIRS "hpdf.h")
if(LIBHARU_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_LIBHARU true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   libharu package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   libharu package not found")
endif()
