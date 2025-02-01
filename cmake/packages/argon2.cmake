#[=[
argon2

repo link: https://github.com/P-H-C/phc-winner-argon2
#]=]
set(LIBPRCPP_PROJECT_USING_ARGON2 false)

find_file(LIBPRCPP_ARGON2_INCLUDE_DIRS "argon2.h") # unix only, not sure in windows for now
if(LIBPRCPP_ARGON2_INCLUDE_DIRS)
    set(LIBPRCPP_PROJECT_USING_ARGON2 true)
    message(NOTICE "-- argon.h found in ${LIBPRCPP_ARGON2_INCLUDE_DIRS}")
else()
    message(NOTICE "-- argon.h not found")
endif()
