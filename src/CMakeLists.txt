cmake_minimum_required(VERSION 3.0.0)

project(Raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SDL2 REQUIRED)

add_executable(Raytracer
     main.cpp
     Raytracer.cpp
     Geometry.cpp
     SDL_Handler.cpp
     Light.cpp
     Color.cpp
    )

target_link_libraries(Raytracer PRIVATE SDL2::SDL2 SDL2::SDL2main)