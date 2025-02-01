mkdir -p build/debug;

cmake -G "Ninja" -B build/debug -DCMAKE_BUILD_TYPE=Debug -DLIBPRCPP_PROJECT_BUILD_TOOLS=true -DLIBPRCPP_PROJECT_BUILD_TESTS=true;

cmake --build build/debug --target all --;
