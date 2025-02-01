set(LIBPRCPP_VCPKG_FOUND false)
set(LIBPRCPP_USING_VCPKG false)

if(LIBPRCPP_USE_VCPKG)
    set(VCPKG_ERROR 0)

    if(NOT LIBPRCPP_VCPKG_FOUND)
        message(NOTICE "-- you are using \"vcpkg\" of VCPKG_ROOT env variable as \"$ENV{VCPKG_ROOT}\", using the \"vcpkg\" toolchain")
        if("$ENV{VCPKG_ROOT}" STREQUAL "")
            message(NOTICE "-- VCPKG_ROOT env variable is empty")
            set(VCPKG_ERROR 1)
        else()
            include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
            set(LIBPRCPP_VCPKG_FOUND true)
        endif()
    endif()

    if(NOT LIBPRCPP_VCPKG_FOUND)
        message(NOTICE "-- you are using \"vcpkg\" of VCPKG_DIR env variable as \"$ENV{VCPKG_DIR}\", using the \"vcpkg\" toolchain")
        if("$ENV{VCPKG_DIR}" STREQUAL "")
            message(NOTICE "-- VCPKG_DIR env variable is empty")
            set(VCPKG_ERROR 2)
        else()
            include("$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
            set(LIBPRCPP_VCPKG_FOUND true)
        endif()
    endif()

    if(NOT VCPKG_ERROR EQUAL 0)
        message(FATAL_ERROR "-- you are attempting using vcpkg, but \"VCPKG_DIR\" or \"VCPKG_ROOT\" is not set as environment variable since LIBPRCPP_USE_VCPKG is true/ON")
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

        if(NOT VCPKG_TRIPLET)
            message(FATAL_ERROR "-- VCPKG_TRIPLET is not defined, supported list:\n
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
            message(NOTICE "-- Using vcpkg installed directories for triplet: ${VCPKG_TRIPLET}")
            
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

            set(LIBPRCPP_USING_VCPKG true)
        else()
            message(FATAL_ERROR "-- The VCPKG install directory does not exist: ${VCPKG_INSTALL_DIR}")
        endif()
    endif()
endif()
