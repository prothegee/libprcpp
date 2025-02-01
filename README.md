# libprcpp

one stop c++ library for c++ project

currently for personal use as module

<br>

---

## package that might required

- [argon2](https://github.com/P-H-C/phc-winner-argon2)
- [openssl](https://github.com/openssl/openssl)
<!-- - [jwt cpp](https://github.com/Thalhammer/jwt-cpp) -->
<!-- - [libharu](https://github.com/libharu/libharu) -->
- [drogon framework](https://github.com/drogonframework/drogon)
- [scylla cpp driver](https://github.com/scylladb/cpp-driver)

__*NOTES:*__
```
- if above package doesn't exists project will skip that package library
- may cause some module & functionality not implemented
```

- third parties/vendors packages:
    - [stb](./vendors/stb/stb/README.md)
    - [sdl](./vendors/sdl/README.md)
    - [jsoncpp](./vendors/jsoncpp/README.md)
    - [nanosvg](./vendors/nanosvg/README.md)
    - [zxing-cpp](./vendors/zxing-cpp/README.md)
    - [cryptopp cmake](./vendors/cryptopp-cmake/README.md)

<br>

---

## tested compiler

- [X] Clang ( 14.0 )
- [X] GNU GCC ( 12.2 )
- [X] Microsoft MSVC ( 19.42 )

<br>

---

## tested OS

- [X] Microsoft Windows ( 11 )
- [X] GNU/Linux Debian Bookworm ( 12 )

<br>

---

## cmake

- build:
    ```cmake
    cmake -G "Ninja" -B build/debug -DCMAKE_BUILD_TYPE=Debug;
    cmake --build build/debug --target all --;
    ```

- options:
    ```cmake
    # build shared lib
    # default false or OFF
    BUILD_SHARED_LIBS

    # custom install prefix
    # default "" or empty
    CMAKE_INSTALL_PREFIX

    # build libprcpp tests
    # default false or OFF
    LIBPRCPP_PROJECT_BUILD_TESTS

    # build libprcpp tools
    # default false or OFF
    LIBPRCPP_PROJECT_BUILD_TOOLS

    # build using vcpkg
    # default false or OFF
    # if true/ON, this will lookup for environment variable of:
    # - VCPKG_DIR
    # - VCPKG_ROOT
    # - VCPKG_DEFAULT_TRIPLET / VCPKG_TRIPLET
    LIBPRCPP_USE_VCPKG

    # set manual vcpkg triplet
    # default "" or empty
    # available triplets:
    # - x86-linux
    # - x64-linux
    # - arm64-linux
    # - arm-linux
    # - x86-windows
    # - x64-window
    # - x86-osx
    # - x64-osx
    # - arm64-osx
    # - arm-android
    # - x86-android
    # - x64-android
    # - arm64-android
    # - x86-ios
    # - x64-ios
    # - arm-ios
    # - arm64-ios
    LIBPRCPP_VCPKG_TRIPLET
    ```

<br>

---

###### end of libprcpp README
