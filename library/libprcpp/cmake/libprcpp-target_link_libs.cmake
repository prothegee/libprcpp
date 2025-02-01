# use thread
if(LIBPRCPP_PROJECT_USING_THREADS)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE Threads::Threads)
endif()

# use jsoncpp
if(LIBPRCPP_PROJECT_USING_JSONCPP)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE jsoncpp_static)
endif()

# use openssl
if(LIBPRCPP_PROJECT_USING_OPENSSL)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

# use drogon
if(LIBPRCPP_PROJECT_USING_DROGON_FRAMEWORK)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE Drogon::Drogon)
endif()

# use cryptopp-cmake
if(LIBPRCPP_PROJECT_USING_CRYPTOPP_CMAKE)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE cryptopp::cryptopp)
endif()

# use argon2
if(LIBPRCPP_PROJECT_USING_ARGON2)        
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE argon2)
endif()

# use scylla-cpp-driver
if(LIBPRCPP_PROJECT_USING_SCYLLADB)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE scylla-cpp-driver)
endif()

# use jwt-cpp
if(LIBPRCPP_PROJECT_USING_JWT_CPP)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE jwt-cpp::jwt-cpp)
endif()

# use libharu
if(LIBPRCPP_PROJECT_USING_LIBHARU)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE hpdf)
endif()

# use lunasvg
if(LIBPRCPP_PROJECT_USING_LUNASVG)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE lunasvg::lunasvg)
endif()

# use nanosvg
if(LIBPRCPP_PROJECT_USING_NANOSVG)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE nanosvg nanosvgrast)
endif()

# use zxing-cpp
if(LIBPRCPP_PROJECT_USING_ZXING_CPP)
    target_link_libraries(${LIBPRCPP_PROJECT} PRIVATE ZXing::Core ZXing::ZXing)
endif()

# use stb
if(LIBPRCPP_PROJECT_USING_STB)
    target_include_directories(${LIBPRCPP_PROJECT} PRIVATE ${Stb_INCLUDE_DIR})
endif()
