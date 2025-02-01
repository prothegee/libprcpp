if(NOT DEFINED LIBPRCPP_PROJECT_BUILD_TOOLS)
    set(LIBPRCPP_PROJECT_BUILD_TOOLS false)
endif()


if(NOT DEFINED LIBPRCPP_PROJECT_BUILD_TESTS)
    set(LIBPRCPP_PROJECT_BUILD_TESTS false)
endif()


if(NOT DEFINED ZXING_EXPERIMENTAL_API)
    set(ZXING_EXPERIMENTAL_API true)
endif()


# base system variables
string(TOLOWER ${CMAKE_SYSTEM_NAME}      LIBPRCPP_SYSTEM_NAME)
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} LIBPRCPP_SYSTEM_PROCESSOR)
string(TOLOWER ${CMAKE_BUILD_TYPE}       LIBPRCPP_SYSTEM_BUILD_TYPE)


# compiler used list
set(LIBPRCPP_COMPILER_GNU   false)
set(LIBPRCPP_COMPILER_MSVC  false)
set(LIBPRCPP_COMPILER_CLANG false)


# define compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(LIBPRCPP_COMPILER_GNU   true)
    set(LIBPRCPP_COMPILER_MSVC  false)
    set(LIBPRCPP_COMPILER_CLANG false)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(LIBPRCPP_COMPILER_GNU   false)
    set(LIBPRCPP_COMPILER_MSVC  true)
    set(LIBPRCPP_COMPILER_CLANG false)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(LIBPRCPP_COMPILER_GNU   false)
    set(LIBPRCPP_COMPILER_MSVC  false)
    set(LIBPRCPP_COMPILER_CLANG true)
else()
    message(WARNING "-- libprcpp-project:\n   cmake compiler id is not configured & not supported")
endif()


# executeable linker flags
if(NOT DEFINED CMAKE_EXE_LINKER_FLAGS)
    set(CMAKE_EXE_LINKER_FLAGS "")
endif()


# cxx flags
if(NOT DEFINED CMAKE_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "")
endif()


# c++ standard
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
elseif(CMAKE_CXX_STANDARD LESS 17)
    set(CMAKE_CXX_STANDARD 17)
else()
    set(CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD})
endif()


# libprcpp is debug stats
set(LIBPRCPP_IS_DEBUG false)


# [V] 0:undefined
# [V] 1:linux
# [V] 2:windows
# [V] 3:macos
# [X] 4:android
# [X] 5:ios
# [X] 6:web
# [X] 7:ps
# [X] 8:xbox
# [X] 9:nintendo
set(LIBPRCPP_BUILD_TARGET 0)

# assign build target num
if(${LIBPRCPP_SYSTEM_NAME} STREQUAL "linux")
    set(LIBPRCPP_BUILD_TARGET 1)
elseif(${LIBPRCPP_SYSTEM_NAME} STREQUAL "windows")
    set(LIBPRCPP_BUILD_TARGET 2)
elseif(${LIBPRCPP_SYSTEM_NAME} STREQUAL "macos")
    set(LIBPRCPP_BUILD_TARGET 3)
else()
    message(NOTICE "-- ${PROJECT_NAME}:\n   build system is unknown")
endif()

# manual assign to LIBPRCPP_BUILD_TARGET?


# 0:undefined 1:debug 2:staging 3:demo 4:release
set(LIBPRCPP_BUILD_STATUS 0)


# libprcpp build status
if(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "debug")
    set(LIBPRCPP_BUILD_STATUS 1)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "profile")
    set(LIBPRCPP_BUILD_STATUS 1)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "relwithdebinfo")
    set(LIBPRCPP_BUILD_STATUS 2)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "release")
    set(LIBPRCPP_BUILD_STATUS 3)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "minsizerel")
    set(LIBPRCPP_BUILD_STATUS 4)
endif()


# libprcpp debug status, release & misizerel is not debug
if(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "release")
    set(LIBPRCPP_IS_DEBUG false)
elseif(LIBPRCPP_SYSTEM_BUILD_TYPE STREQUAL "minsizerel")
    set(LIBPRCPP_IS_DEBUG false)
else()
    set(LIBPRCPP_IS_DEBUG true)
endif()


# libprcpp output dir
set(LIBPRCPP_OUTPUT_DIR)


# libprcpp install dir
set(LIBPRCPP_INSTALL_DIR)


# preparing out binary dir
if(NOT EXISTS "${CMAKE_BINARY_DIR}/out")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/out")
endif()
