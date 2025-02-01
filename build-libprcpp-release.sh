mkdir -p build/release;

cmake -G "Ninja" -B build/release -DCMAKE_BUILD_TYPE=Release -DLIBPRCPP_PROJECT_BUILD_TOOLS=true -DLIBPRCPP_PROJECT_BUILD_TESTS=true;

cmake --build build/release --target all --;
