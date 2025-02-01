#[=[
scylladb cpp driver

repo link: https://github.com/scylladb/cpp-driver

===========================================

you may run this after installing scylla-cpp-driver
```sh
sudo ln -s /usr/local/lib/x86_64-linux-gnu/libscylla-cpp-driver.so /usr/local/lib/;
# or
sudo ln -s /usr/local/lib/x86_64-linux-gnu/libscylla-cpp-driver.so.2 /usr/local/lib/;

# depending on your scylla-cpp-driver, it may be different on SOVERSION

# then 
sudo ldconfig;
```

===========================================

this one currently only work on linux for this project
#]=]
set(LIBPRCPP_PROJECT_USING_SCYLLADB false)

find_file(LIBPRCPP_CASSANDRA_HEADER "cassandra.h")
find_file(LIBPRCPP_SCYLLA_EXECUTEABLE "scylla")

if(LIBPRCPP_CASSANDRA_HEADER AND LIBPRCPP_SCYLLA_EXECUTEABLE)
    set(LIBPRCPP_PROJECT_USING_SCYLLADB true)
    message(NOTICE "-- cassandra.h found in ${LIBPRCPP_CASSANDRA_HEADER}")
    message(NOTICE "-- scylla executeable found in ${LIBPRCPP_SCYLLA_EXECUTEABLE}")
else()
    message(NOTICE "-- cassandra.h not found")
    message(NOTICE "-- scylla executeable not found")
endif()
