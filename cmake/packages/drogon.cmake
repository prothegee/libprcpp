#[=[
cryptopp

repo link: https://github.com/drogonframework/drogon
#]=]
set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK false)

find_package(Drogon CONFIG)
if(Drogon_FOUND)
    set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK true)
    message(NOTICE "-- drogon-framework package found")
else()
    message(NOTICE "-- drogon-framework package not found")
endif()

# link against shared lib
set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK_LIB false)

if(NOT DEFINED LIBPRCPP_DROGON_FRAMEWORK_LIBRARY)
    set(LIBPRCPP_DROGON_FRAMEWORK_LIBRARY)
endif()

find_library(LIBPRCPP_DROGON_FRAMEWORK_LIBRARY drogon)
if(LIBPRCPP_DROGON_FRAMEWORK_LIBRARY)
    set(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK_LIB true)
    message(NOTICE "-- drogon-framework lib found")
else()
    message(NOTICE "-- drogon-framework lib not found")
endif()
