include(CheckIncludeFileCXX)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

set(PROJECT_SYSTEM_PROCESSOR "${CMAKE_SYSTEM_PROCESSOR}")

if(PROJECT_BUILD_TARGET EQUAL 1) # linux
    if(PROJECT_BUILD_STATUS EQUAL 1)
        set(PROJECT_BUILD_TAGET_DIRECTORY "linux_${PROJECT_SYSTEM_PROCESSOR}/debug")
    elseif(PROJECT_BUILD_STATUS EQUAL 2)
        set(PROJECT_BUILD_TAGET_DIRECTORY "linux_${PROJECT_SYSTEM_PROCESSOR}/staging")
    elseif(PROJECT_BUILD_STATUS EQUAL 3)
        set(PROJECT_BUILD_TAGET_DIRECTORY "linux_${PROJECT_SYSTEM_PROCESSOR}/demo")
    elseif(PROJECT_BUILD_STATUS EQUAL 4)
        set(PROJECT_BUILD_TAGET_DIRECTORY "linux_${PROJECT_SYSTEM_PROCESSOR}/release")
    else()
        message(FATAL_ERROR "${PROJECT_NAME}:\n   -DPROJECT_BUILD_STATUS is undefined or not supported")
    endif()
elseif(PROJECT_BUILD_TARGET EQUAL 2) # windows
    if(PROJECT_BUILD_STATUS EQUAL 1)
        set(PROJECT_BUILD_TAGET_DIRECTORY "windows_${PROJECT_SYSTEM_PROCESSOR}/debug")
    elseif(PROJECT_BUILD_STATUS EQUAL 2)
        set(PROJECT_BUILD_TAGET_DIRECTORY "windows_${PROJECT_SYSTEM_PROCESSOR}/staging")
    elseif(PROJECT_BUILD_STATUS EQUAL 3)
        set(PROJECT_BUILD_TAGET_DIRECTORY "windows_${PROJECT_SYSTEM_PROCESSOR}/demo")
    elseif(PROJECT_BUILD_STATUS EQUAL 4)
        set(PROJECT_BUILD_TAGET_DIRECTORY "windows_${PROJECT_SYSTEM_PROCESSOR}/release")
    else()
        message(FATAL_ERROR "${PROJECT_NAME}:\n   -DPROJECT_BUILD_STATUS is undefined or not supported")
    endif()
elseif(PROJECT_BUILD_TARGET EQUAL 3) # osx
    if(PROJECT_BUILD_STATUS EQUAL 1)
        set(PROJECT_BUILD_TAGET_DIRECTORY "osx_${PROJECT_SYSTEM_PROCESSOR}/debug")
    elseif(PROJECT_BUILD_STATUS EQUAL 2)
        set(PROJECT_BUILD_TAGET_DIRECTORY "osx_${PROJECT_SYSTEM_PROCESSOR}/staging")
    elseif(PROJECT_BUILD_STATUS EQUAL 3)
        set(PROJECT_BUILD_TAGET_DIRECTORY "osx_${PROJECT_SYSTEM_PROCESSOR}/demo")
    elseif(PROJECT_BUILD_STATUS EQUAL 4)
        set(PROJECT_BUILD_TAGET_DIRECTORY "osx_${PROJECT_SYSTEM_PROCESSOR}/release")
    else()
        message(FATAL_ERROR "${PROJECT_NAME}:\n   -DPROJECT_BUILD_STATUS is undefined or not supported")
        endif()
else()
    message(FATAL_ERROR "${PROJECT_NAME}:\n   -DPROJECT_BUILD_TARGET is undefined or not supported")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Profile")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_BUILD_TYPE "Release")
else()
    message(FATAL_ERROR "-DCMAKE_BUILD_TYPE is not recognized")
endif()

if(PROJECT_USING_BUILD_TAGET_DIRECTORY)
    set(EXECUTABLE_OUTPUT_PATH          ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
    set(CMAKE_PDB_OUTPUT_DIRECTORY      ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
endif()