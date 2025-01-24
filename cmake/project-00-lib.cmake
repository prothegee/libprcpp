string(TOLOWER ${CMAKE_SYSTEM_NAME}      LIBPRCPP_BASE_SYSTEM_NAME)
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} LIBPRCPP_BASE_SYSTEM_PROCESSOR)
string(TOLOWER ${CMAKE_BUILD_TYPE}       LIBPRCPP_BASE_SYSTEM_BUILD_TYPE)

set(LIBPRCPP_BASE_COMPILER_GNU   false)
set(LIBPRCPP_BASE_COMPILER_MSVC  false)
set(LIBPRCPP_BASE_COMPILER_CLANG false)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(LIBPRCPP_BASE_COMPILER_GNU   true)
    set(LIBPRCPP_BASE_COMPILER_MSVC  false)
    set(LIBPRCPP_BASE_COMPILER_CLANG false)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(LIBPRCPP_BASE_COMPILER_GNU   false)
    set(LIBPRCPP_BASE_COMPILER_MSVC  true)
    set(LIBPRCPP_BASE_COMPILER_CLANG false)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(LIBPRCPP_BASE_COMPILER_GNU   false)
    set(LIBPRCPP_BASE_COMPILER_MSVC  false)
    set(LIBPRCPP_BASE_COMPILER_CLANG true)
else()
    # IGNORED
endif()

#[====================================[
PRECONFIGURE COMPILER flags for:
- CMAKE_CXX_FLAGS
- CMAKE_EXE_LINKER_FLAGS
#]====================================]
if(LIBPRCPP_BASE_COMPILER_GNU)
    set(CMAKE_CXX_FLAGS "-lm")
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-no-pie")
endif()
if(LIBPRCPP_BASE_COMPILER_MSVC)
    # skipped
endif()
if(LIBPRCPP_BASE_COMPILER_CLANG)
    set(CMAKE_CXX_FLAGS "-fPIC -v -lm -ldl")
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-no-pie")
endif()

set(CMAKE_CXX_STANDARD 17)

if(${CMAKE_CXX_STANDARD} LESS_EQUAL 17)
    set(CMAKE_CXX_STANDARD 17)
endif()

# start: check toolchain
if("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    message(NOTICE "-- ${PROJECT_NAME}:\n   cmake toolchain file is empty")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   including cmake toolchain file \"${CMAKE_TOOLCHAIN_FILE}\"")
    include(${CMAKE_TOOLCHAIN_FILE})
endif()
# end: check toolchain

# start: vcpkg
set(LIBPRCPP_VCPKG_FOUND false)

if(LIBPRCPP_VCPKG)
    set(VCPKG_ERROR 0)

    if(NOT LIBPRCPP_VCPKG_FOUND)
        message(NOTICE "-- ${PROJECT_NAME}:\n   you are using \"vcpkg\" of VCPKG_ROOT env variable as \"$ENV{VCPKG_ROOT}\", using the \"vcpkg\" toolchain")
        if("$ENV{VCPKG_ROOT}" STREQUAL "")
            message(NOTICE "-- ${PROJECT_NAME}:\n   VCPKG_ROOT env variable is empty")
            set(VCPKG_ERROR 1)
        else()
            include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
            set(LIBPRCPP_VCPKG_FOUND true)
        endif()
    endif()

    if(NOT LIBPRCPP_VCPKG_FOUND)
        message(NOTICE "-- ${PROJECT_NAME}:\n   you are using \"vcpkg\" of VCPKG_DIR env variable as \"$ENV{VCPKG_DIR}\", using the \"vcpkg\" toolchain")
        if("$ENV{VCPKG_DIR}" STREQUAL "")
            message(NOTICE "-- ${PROJECT_NAME}:\n   VCPKG_DIR env variable is empty")
            set(VCPKG_ERROR 2)
        else()
            include("$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
            set(LIBPRCPP_VCPKG_FOUND true)
        endif()
    endif()

    if(NOT VCPKG_ERROR EQUAL 0)
        message(FATAL_ERROR "-- ${PROJECT_NAME}:\n   you are attempting using vcpkg, but \"VCPKG_DIR\" or \"VCPKG_ROOT\" is not set as environment variable")
    endif()

    if(LIBPRCPP_VCPKG_FOUND)
        set(VCPKG_TRIPLET_ERROR 0)
        if("$ENV{VCPKG_DEFAULT_TRIPLET}" STREQUAL "")
            set(VCPKG_TRIPLET_ERROR 1)
        else()
            set(VCPKG_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}")            
        endif()

        if(VCPKG_TRIPLET_ERROR EQUAL 1)
            if("${LIBPRCPP_VCPKG_TRIPLET}" STREQUAL "")
                set(VCPKG_TRIPLET_ERROR 2)
            else()
                set(VCPKG_TRIPLET "${LIBPRCPP_VCPKG_TRIPLET}")  
            endif()
        endif()

        # message(WARNING "VCPKG_DEFAULT_TRIPLET: $ENV{VCPKG_DEFAULT_TRIPLET}\nLIBPRCPP_VCPKG_TRIPLET: ${LIBPRCPP_VCPKG_TRIPLET}")

        if(NOT VCPKG_TRIPLET)
            message(FATAL_ERROR "-- ${PROJECT_NAME}:\n   VCPKG_TRIPLET is not defined, supported list:\n
- x86-linux
- x64-linux
- arm64-linux
- arm-linux
- x86-windows
- x64-window
- x86-osx
- x64-osx
- arm64-osx
- arm-android
- x86-android
- x64-android
- arm64-android
- x86-ios
- x64-ios
- arm-ios
- arm64-ios"
            )
        endif()

        set(VCPKG_INSTALL_DIR "$ENV{VCPKG_ROOT}/installed/${VCPKG_TRIPLET}")
        if(EXISTS "${VCPKG_INSTALL_DIR}")
            message(NOTICE "-- ${PROJECT_NAME}:\n   Using vcpkg installed directories for triplet: ${VCPKG_TRIPLET}")
            
            include_directories(
                "${VCPKG_INSTALL_DIR}/include"
                "${VCPKG_INSTALL_DIR}/debug/include"
            )

            link_directories(
                "${VCPKG_INSTALL_DIR}/lib"
                "${VCPKG_INSTALL_DIR}/debug/lib"
            )

            set(CMAKE_PROGRAM_PATH
                "${VCPKG_INSTALL_DIR}/bin"
                "${VCPKG_INSTALL_DIR}/debug/bin"
            )

            set(CMAKE_PREFIX_PATH
                "${VCPKG_INSTALL_DIR}/share"
            )
        else()
            message(FATAL_ERROR "-- ${PROJECT_NAME}:\n   The VCPKG install directory does not exist: ${VCPKG_INSTALL_DIR}")
        endif()
    endif()
endif()
# end: vcpkg


# start: threads
set(LIBPRCPP_PROJECT_USING_THREADS false)

find_package(Threads)
if(Threads_FOUND)
    set(LIBPRCPP_PROJECT_USING_THREADS true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   threads package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   threads package not found")
endif()
# end: threads


# start: jsoncpp
set(LIBPRCPP_PROJECT_USING_JSONCPP false)

find_package(jsoncpp CONFIG)
if(jsoncpp_FOUND)
    set(LIBPRCPP_PROJECT_USING_JSONCPP true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package found ${JSONCPP_LIBRARIES}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package not found try find path default include dir")
    if(JSONCPP_INCLUDE_DIR)
        message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package found as path in ${JSONCPP_INCLUDE_DIR}")
        set(LIBPRCPP_PROJECT_USING_JSONCPP true)
        include_directories(${JSONCPP_LIBRARIES})
    else()
        message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp package not found in default dir, try find file")
        find_file(LIBPRCPP_JSONCPP_INCLUDE_DIRS "json/json.h")
        if(LIBPRCPP_JSONCPP_INCLUDE_DIRS)
            set(LIBPRCPP_PROJECT_USING_JSONCPP true)
            message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp path found as path in ${LIBPRCPP_JSONCPP_INCLUDE_DIRS}")
        else()
            message(NOTICE "-- ${PROJECT_NAME}:\n   jsoncpp path not found in default include dir and when try to find file")
        endif()
    endif()
endif()
# end: jsoncpp


# start: openssl
set(LIBPRCPP_PROJECT_USING_OPENSSL false)

find_package(OpenSSL CONFIG)
if(OpenSSL_FOUND)
    set(LIBPRCPP_PROJECT_USING_OPENSSL true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package not found try find path default include dir")
    if(OPENSSL_INCLUDE_DIR)
        message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package found as path in ${OPENSSL_INCLUDE_DIR}")
        set(LIBPRCPP_PROJECT_USING_OPENSSL true)
        include_directories(${OPENSSL_LIBRARIES})
    else()
        message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL package not found in default dir, try find file")
        find_file(LIBPRCPP_OPENSSL_INCLUDE_DIRS "openssl/evp.h")
        if(LIBPRCPP_OPENSSL_INCLUDE_DIRS)
            set(LIBPRCPP_PROJECT_USING_OPENSSL true)
            message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL path found as path in ${LIBPRCPP_OPENSSL_INCLUDE_DIRS}")
        else()
            message(NOTICE "-- ${PROJECT_NAME}:\n   OpenSSL path not found in default include dir and when try to find file")
        endif()
    endif()
endif()
# end: openssl


# start: drogon framework
set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK false)

find_package(Drogon CONFIG)
if(Drogon_FOUND)
    set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   Drogon Framework package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   Drogon Framework package not found")
endif()
# end: drogon framework


# start: cryptopp-cmake
set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE false)

find_package(cryptopp CONFIG)
if(cryptopp_FOUND)
    set(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   cryptopp-cmake package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   cryptopp-cmake package not found")
endif()
# end: cryptopp-cmake


# start: argon2
set(LIBPRCPP_PROJECT_USING_ARGON2 false)

find_file(LIBPRCPP_ARGON2_INCLUDE_DIRS "argon2.h") # unix only, not sure in windows for now
if(LIBPRCPP_ARGON2_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_ARGON2 true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   argon.h found in ${LIBPRCPP_ARGON2_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   argon.h not found")
endif()
# end: argon2


# start: postgresql
set(LIBPRCPP_PROJECT_USING_POSTGRESQL false)
set(LIBPRCPP_PROJECT_USING_POSTGRESQL_HAS_PARENT_DIR false)

find_package(PostgreSQL CONFIG)
if(PostgreSQL_FOUND)
    set(LIBPRCPP_PROJECT_USING_POSTGRESQL true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   postgresql package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   postgresql package not found")
    if(PostgreSQL_INCLUDE_DIR)
        message(NOTICE "-- ${PROJECT_NAME}:\n   postgresql package found as path in ${PostgreSQL_INCLUDE_DIR}")
        set(LIBPRCPP_PROJECT_USING_POSTGRESQL true)
        include_directories(${PostgreSQL_INCLUDE_DIR})
    else()
        message(NOTICE "-- ${PROJECT_NAME}:\n   postgresql package not found in default dir, try find file")
        find_file(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS "postgresql/libpq-fe.h")
        if(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS)
            set(LIBPRCPP_PROJECT_USING_POSTGRESQL true)
            include_directories(${LIBPRCPP_POSTGRESQL_INCLUDE_DIRS})
            message(NOTICE "-- ${PROJECT_NAME}:\n   postgresql path found as path in ${LIBPRCPP_POSTGRESQL_INCLUDE_DIRS}")
        else()
            message(NOTICE "-- ${PROJECT_NAME}:\n   postgresql path not found in default include dir and when try to find file")
        endif()
    endif()

    if(LIBPRCPP_PROJECT_USING_POSTGRESQL)
        if(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS MATCHES "postgresql/libpq-fe.h")
            set(LIBPRCPP_PROJECT_USING_POSTGRESQL_HAS_PARENT_DIR true)
        endif()
    endif()
endif()
# start: postgresql


# start: scylladb *but somehow cassandra
set(LIBPRCPP_PROJECT_USING_SCYLLADB false)

find_file(LIBPRCPP_CASS_CPP_INCLUDE_DIRS "cassandra.h")
if(LIBPRCPP_CASS_CPP_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_SCYLLADB true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   cassandra.h found in ${LIBPRCPP_CASS_CPP_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   cassandra.h not found")
endif()
# end: scylladb


# start: jwt-cpp
set(LIBPRCPP_PROJECT_USING_JWT_CPP false)

find_file(LIBPRCPP_JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h")
if(LIBPRCPP_JWT_CPP_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_JWT_CPP true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   jwt-cpp header found in ${LIBPRCPP_JWT_CPP_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   jwt-cpp header not found")
endif()
# end: jwt-cpp


# start: libharu
set(LIBPRCPP_PROJECT_USING_LIBHARU false)

find_file(LIBPRCPP_LIBHARU_INCLUDE_DIRS "hpdf.h")
if(LIBPRCPP_LIBHARU_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_LIBHARU true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   libharu header found in ${LIBPRCPP_LIBHARU_INCLUDE_DIRS}")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   libharu header not found")
endif()
# end: libharu


# start: stb
#[====================================[
ZXing build help:

- clone the repo

- run
```sh
cmake -G "Ninja" -S zxing-cpp -B zxing-cpp.release -DCMAKE_BUILD_TYPE=Release -DZXING_EXPERIMENTAL_API=true
cmake --build zxing-cpp.release --config all
sudo cmake --install zxing-cpp.release

cmake -G "Ninja" -S zxing-cpp -B zxing-cpp.debug -DCMAKE_BUILD_TYPE=Debug -DZXING_EXPERIMENTAL_API=true
cmake --build zxing-cpp.debug --config all
sudo cmake --install zxing-cpp.debug

# may required to use -DCMAKE_INSTALL_PREFIX=/path/to/install as seperate debug and release lib
```

- you need to include that dir

------------------------------------------

may requires:
- STB_IMAGE_WRITE_IMPLEMENTATION
- STB_IMAGE_IMPLEMENTATION
]====================================]
set(LIBPRCPP_PROJECT_USING_STB false)
set(LIBPRCPP_PROJECT_USING_STB_HAS_PARENT_DIR false)

if(LIBPRCPP_BASE_SYSTEM_NAME STREQUAL "windows")
    find_package(Stb)
else()
    find_package(Stb CONFIG) # Has warning if CONFIG not passed
endif()

if(Stb_FOUND)
    set(LIBPRCPP_PROJECT_USING_STB true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   Stb found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   Stb not found, attempt to check file")
    find_file(LIBPRCPP_STB_INCLUDE_DIRS "stb/stb_image_write.h")
    if(LIBPRCPP_STB_INCLUDE_DIRS)
        set(LIBPRCPP_PROJECT_USING_STB true)
        include_directories(${LIBPRCPP_STB_INCLUDE_DIRS})
        message(NOTICE "-- ${PROJECT_NAME}:\n   stb path found as path in ${LIBPRCPP_STB_INCLUDE_DIRS} attempt #1")
    else()
        message(NOTICE "-- ${PROJECT_NAME}:\n   stb path not found in default include dir and when try to find file")
    endif()

    if(LIBPRCPP_PROJECT_USING_STB)
        if(LIBPRCPP_STB_INCLUDE_DIRS MATCHES "stb/stb_image_write.h")
            set(LIBPRCPP_PROJECT_USING_STB_HAS_PARENT_DIR true)
        endif()
    endif()
endif()

if(NOT ${Stb_INCLUDE_DIR} STREQUAL "")
    if(Stb_DIR STREQUAL "")
        set(Stb_DIR "${Stb_INCLUDE_DIR}")
    endif()
    include_directories(${Stb_INCLUDE_DIR})
endif()
# end: stb


# start: lunasvg
set(LIBPRCPP_PROJECT_USING_LUNASVG false)

find_package(lunasvg CONFIG)

if(lunasvg_FOUND)
    set(LIBPRCPP_PROJECT_USING_LUNASVG true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   lunasvg package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   lunasvg package not found")
endif()
# end: lunasvg


# start: zxing
set(LIBPRCPP_PROJECT_USING_ZXING false)

find_package(ZXing CONFIG)
if(ZXing_FOUND)
    set(ZXING_EXPERIMENTAL_API true)
    set(LIBPRCPP_PROJECT_USING_ZXING true)
    message(NOTICE "-- ${PROJECT_NAME}:\n   libzxing package found")
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   libzxing package not found")
endif()
# end: zxing
