# libprcpp

one stop c++ library for c++ project

currently for personal use as module

<!--
will never reach v1.x.x if not cross compiled on linux, windows, macos, android, & ios
-->

<br>

---

## package that might required

- [argon2](https://github.com/P-H-C/phc-winner-argon2)
- [openssl](https://github.com/openssl/openssl)
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
    - [libharu](./vendors/libharu/README.md)
    - [nanosvg](./vendors/nanosvg/README.md)
    - [zxing-cpp](./vendors/zxing-cpp/README.md)
    - [cryptopp-cmake](./vendors/cryptopp-cmake/README.md)

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
    mkdir -p build/debug;
    cmake -G "Ninja" -B build/debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-std:c++17"; # use "/std:c++17 /EHsc" for msvc
    cmake --build build/debug --target all --;
    ```

<br>

---

###### end of libprcpp README
