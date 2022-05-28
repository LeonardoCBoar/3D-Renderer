
cmake_minimum_required(VERSION 3.0.0)

project(RaytracerTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


add_executable(RaytracerTests
    Tests.cpp
    ../src/Geometry.cpp
    ../src/Light.cpp
    ../src/Raytracer.cpp
    ../src/Color.cpp
    )

find_package(SDL2 REQUIRED)
target_link_libraries(RaytracerTests PRIVATE SDL2::SDL2 SDL2::SDL2main)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(RaytracerTests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)