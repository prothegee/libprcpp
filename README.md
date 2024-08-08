# libprcpp

one stop c++ library for c++ project integration

<br>

---

## package that might required

- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- [openssl](https://github.com/openssl/openssl)
- [jwt cpp](https://github.com/Thalhammer/jwt-cpp)
- [libharu](https://github.com/libharu/libharu)
- [cryptopp cmake](https://github.com/abdes/cryptopp-cmake)
- [drogon framework](https://github.com/drogonframework/drogon)
- [scylla cpp driver](https://github.com/scylladb/cpp-driver)

__*NOTES:*__
```
- if above package doesn't exists project will skip that package library
- may cause some module not implemented
```

<br>

---

## cmake

`cmake conf`
```sh
# required
-DPROJECT_BUILD_STATUS=1                  # 0:undefined 1:debug 2:staging 3:demo 4:release

# required
-DPROJECT_BUILD_TARGET=1                  # 0:undefined 1:linux 2:windows 3:osx

# not required | default false
-DPROJECT_BUILD_TEST=true                 # will add test directory execute-able

# not required | default false
-PROJECT_USING_BUILD_TAGET_DIRECTORY=true # will make output under PROJECT_BUILD_TAGET_DIRECTORY
```

look on [cmake directory for more info](./cmake)

<br>

`cmake build debug`
```sh
mkdir -p build/debug;
cmake -B build/debug -DCMAKE_CXX_FLAGS="-std=c++17" -DCMAKE_BUILD_TYPE=Debug -DPROJECT_BUILD_STATUS=1 -DPROJECT_BUILD_TARGET=1 -DPROJECT_BUILD_TEST=false -PROJECT_USING_BUILD_TAGET_DIRECTORY=true;
cmake --build build/debug --config Debug;
```

<br>

---

###### end of libprcpp
