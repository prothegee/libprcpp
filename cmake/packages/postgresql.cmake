#[=[
postgresql
#]=]
set(LIBPRCPP_PROJECT_USING_POSTGRESQL false)
set(LIBPRCPP_PROJECT_USING_POSTGRESQL_HAS_PARENT_DIR false)

find_package(PostgreSQL CONFIG)
if(PostgreSQL_FOUND)
    set(LIBPRCPP_PROJECT_USING_POSTGRESQL true)
    message(NOTICE "-- postgresql package found")

    include_directories(${PostgreSQL_INCLUDE_DIR})
else()
    message(NOTICE "-- postgresql package not found")
    message(NOTICE "-- postgresql attempt search #1")
    if(PostgreSQL_INCLUDE_DIR)
        message(NOTICE "-- postgresql package found as path in ${PostgreSQL_INCLUDE_DIR}")
        set(LIBPRCPP_PROJECT_USING_POSTGRESQL true)
        include_directories(${PostgreSQL_INCLUDE_DIR})
    else()
        message(NOTICE "-- postgresql package not found in default dir, try find file")
        find_file(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS "postgresql/libpq-fe.h")
        if(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS)
            set(LIBPRCPP_PROJECT_USING_POSTGRESQL true)
            include_directories(${LIBPRCPP_POSTGRESQL_INCLUDE_DIRS})
            message(NOTICE "-- postgresql found in ${LIBPRCPP_POSTGRESQL_INCLUDE_DIRS}")
        else()
            message(NOTICE "-- postgresql package not found")
            message(NOTICE "-- postgresql attempt search #2")
            find_file(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS "libpq-fe.h")
            if(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS)
                set(LIBPRCPP_PROJECT_USING_POSTGRESQL true)
                include_directories(${LIBPRCPP_POSTGRESQL_INCLUDE_DIRS})
                message(NOTICE "-- postgresql found in ${LIBPRCPP_POSTGRESQL_INCLUDE_DIRS}")
            else()
                message(NOTICE "-- postgresql path not found in default include dir and when try to find file")
            endif()
        endif()
    endif()

    if(LIBPRCPP_PROJECT_USING_POSTGRESQL)
        if(LIBPRCPP_POSTGRESQL_INCLUDE_DIRS MATCHES "postgresql/libpq-fe.h")
            set(LIBPRCPP_PROJECT_USING_POSTGRESQL_HAS_PARENT_DIR true)
        endif()
    endif()
endif()
