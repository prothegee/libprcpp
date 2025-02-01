#[=[
jwt-cpp

repo link: https://github.com/Thalhammer/jwt-cpp
#]=]
set(LIBPRCPP_PROJECT_USING_JWT_CPP false)
set(LIBPRCPP_PROJECT_USING_JWT_CPP_HAS_PARENT_DIR false)

find_package(jwt-cpp CONFIG)

if(jwt-cpp_FOUND)
    set(LIBPRCPP_PROJECT_USING_JWT_CPP true)
    message(NOTICE "-- jwt-cpp package found")
else()
    message(NOTICE "-- jwt-cpp package not found")
    message(NOTICE "-- jwt-cpp attempt #1 search")

    find_file(LIBPRCPP_JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h")
    if(LIBPRCPP_JWT_CPP_INCLUDE_DIRS)
        get_filename_component(jwt-cpp_DIR "${LIBPRCPP_JWT_CPP_INCLUDE_DIRS}" DIRECTORY)

        set(LIBPRCPP_PROJECT_USING_JWT_CPP true)
        include_directories("${jwt-cpp_DIR}")
        message(NOTICE "-- jwt-cpp found in ${jwt-cpp_DIR}")
    else()
        message(NOTICE "-- jwt-cpp package not found and not found for related dir") 
    endif()

    if(LIBPRCPP_PROJECT_USING_JWT_CPP)
        if(LIBPRCPP_JWT_CPP_INCLUDE_DIRS MATCHES "jwt-cpp/base.h")
            set(LIBPRCPP_PROJECT_USING_JWT_CPP_HAS_PARENT_DIR true)
        endif()
    endif()
endif()
