#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <iostream>
#include <vector>

#include "Raytracer.hpp"
#include "Vector.hpp"


class SDL_Handler
{ 
    Vector2u16 SCREEN_SIZE{600,600};

    SDL_Window*  window   = nullptr;
    SDL_Renderer* renderer = nullptr;

    Raytracer raytracer
    {
        Vector3d{0,0,0},
        Vector2u16{1,1},
        SCREEN_SIZE,
        1
    };


    public:
        SDL_Handler(const Vector2u16 SCREEN_SIZE = Vector2u16(600,600));
        ~SDL_Handler();

        void sdl_setup();
        void loop();
        void render_screen();

};