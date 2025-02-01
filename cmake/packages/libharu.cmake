#[=[
libharu

repo link: https://github.com/libharu/libharu
#]=]
set(LIBPRCPP_PROJECT_USING_LIBHARU false)

find_file(LIBPRCPP_LIBHARU_INCLUDE_DIRS "hpdf.h")
if(LIBPRCPP_LIBHARU_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_LIBHARU true)
    message(NOTICE "-- libharu header found in ${LIBPRCPP_LIBHARU_INCLUDE_DIRS}")
else()
    message(NOTICE "-- libharu header not found")
endif()
