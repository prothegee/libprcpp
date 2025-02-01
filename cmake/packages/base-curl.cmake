set(LIBPRCPP_FOUND_CURL false)

find_file(LIBPRCPP_CURL_EXECUTEABLE "curl")

if(LIBPRCPP_CURL_EXECUTEABLE)
    set(LIBPRCPP_FOUND_CURL true)
    message(NOTICE "-- curl found in ${LIBPRCPP_CURL_EXECUTEABLE}")
else()
    message(NOTICE "-- curl not found in ${LIBPRCPP_CURL_EXECUTEABLE}")
endif()
