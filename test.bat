
if not exist tests/build mkdir tests/build
if exist tests/build/Debug/RaytracerTests.exe del tests/build/Debug/RaytracerTests.exe

cmake -DCMAKE_TOOLCHAIN_FILE=C:\Libs\vcpkg\scripts\buildsystems\vcpkg.cmake -S tests -B tests/build

cmake --build tests/build

cd tests/build/Debug
RaytracerTests.exe
cd ../../..