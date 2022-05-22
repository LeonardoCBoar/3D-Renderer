if not exist build mkdir build

cmake -DCMAKE_TOOLCHAIN_FILE=C:\Libs\vcpkg\scripts\buildsystems\vcpkg.cmake -S src -B build

cmake --build build