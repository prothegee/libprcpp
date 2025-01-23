# libprcpp

one stop c++ library for c++ project integration

currently for personal use, as module and just reference

<br>

---

## package that might required

- [stb](https://github.com/nothings/stb)
- [argon2](https://github.com/P-H-C/phc-winner-argon2)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- [openssl](https://github.com/openssl/openssl)
- [jwt cpp](https://github.com/Thalhammer/jwt-cpp)
- [libharu](https://github.com/libharu/libharu)
- [zxing-cpp](https://github.com/zxing-cpp/zxing-cpp)
- [cryptopp cmake](https://github.com/abdes/cryptopp-cmake)
- [drogon framework](https://github.com/drogonframework/drogon)
- [scylla cpp driver](https://github.com/scylladb/cpp-driver)

__*NOTES:*__
```
- if above package doesn't exists project will skip that package library
- may cause some module & functionality not implemented
```

<br>

---

## tested operating system

- [V] GNU/Linux Debian 12
- [?] Microsoft Windows (__has error when build test__)
- [X] Apple MacOS/OSX

<br>

---

<!-- ## cmake

`cmake conf`
```sh
# required
# 0:undefined 1:debug 2:staging 3:demo 4:release
-DLIBPRCPP_BUILD_STATUS=1

# required
# 0:undefined 1:linux 2:windows 3:macos_
-DLIBPRCPP_BUILD_TARGET=1

# not required | default false
# error for windows if true, on false is ok
# will add test directory execute-able
-DLIBPRCPP_PROJECT_BUILD_TEST=true

# not required | default false
# will make output under LIBPRCPP_BUILD_TAGET_DIRECTORY
-DLIBPRCPP_PROJECT_USING_BUILD_TAGET_DIRECTORY=true
```

look on [cmake directory for more info](./cmake)

<br>

`cmake build debug - linux`
```sh
mkdir -p build/debug;
cmake -B build/debug -DCMAKE_CXX_FLAGS="-std=c++17" -DCMAKE_BUILD_TYPE=Debug -DLIBPRCPP_BUILD_STATUS=1 -DLIBPRCPP_BUILD_TARGET=1 -DLIBPRCPP_PROJECT_BUILD_TEST=false -DLIBPRCPP_PROJECT_USING_BUILD_TAGET_DIRECTORY=true;
cmake --build build/debug --config Debug;
```

<br>

--- -->

###### end of libprcpp README
