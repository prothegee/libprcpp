#[=[
threads

standard operating system thread library
#]=]
set(LIBPRCPP_PROJECT_USING_THREADS false)

find_package(Threads)
if(Threads_FOUND)
    set(LIBPRCPP_PROJECT_USING_THREADS true)
    message(NOTICE "-- threads package found")
else()
    message(NOTICE "-- threads package not found")
endif()
