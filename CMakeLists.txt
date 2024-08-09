cmake_minimum_required(VERSION 3.15...3.30)
project(libprcpp.project)

# 0:undefined 1:debug 2:staging 3:demo 4:release
set(PROJECT_BUILD_STATUS)

# 0:undefined 1:linux 2:windows 3:osx 4:android 5:ios 6:web 7:ps 8:xbox 9:nintendo
set(PROJECT_BUILD_TARGET)

# 0:undefined 1:GNU 2:MSVC 3:[Cc]lang
set(PROJECT_BUILD_COMPILER_ID)

# processor system type
set(PROJECT_SYSTEM_PROCESSOR)

# this project custom build target directory
set(PROJECT_BUILD_TAGET_DIRECTORY)

# definition of if using build target directory
set(LIBPRCPP_PROJECT_USING_BUILD_TAGET_DIRECTORY)

# this project will build test
set(LIBPRCPP_PROJECT_BUILD_TEST)

# cmake include
include(cmake/project-00-setup.cmake)
include(cmake/project-01-packages.cmake)
include(cmake/project-02-subdirs.cmake)
