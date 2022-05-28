#pragma once

#include <stdint.h>
#include <stdlib.h>  
#include <time.h>
#include <vector>
#include <float.h>

#include <SDL_pixels.h>

#include "Vector.hpp"
#include "Geometry.hpp"
#include "Light.hpp"

inline std::vector<Sphere> tutorial_spheres 
{
    Sphere
    {
        Vector3d{0,-1,3},
        1,
        SDL_Color{255,0,0,255}
    },
    Sphere
    {
        Vector3d{2,0,4},
        1,
        SDL_Color{0,0,255,255}
    },
    Sphere
    {
        Vector3d{-2,0,4},
        1,
        SDL_Color{0,255,0,255}
    },
    Sphere {
        Vector3d{0,-5001,0},
        5000,
        SDL_Color{255,255,0,255}
    }
};

class Raytracer
{
public:
    Vector3d camera_pos;
    Vector2u16 viewport_size;
    Vector2u16 screen_size;

    double viewport_dist;

    const double min_render_dist;
    const double max_render_dist;

    SceneLight light;

    Raytracer(const Vector3d& camera_pos,const Vector2u16& viewport_size,const Vector2u16& screen_size,const double viewport_dist,
              std::vector<Sphere> spheres = tutorial_spheres,const double min_render_dist = 1, const double max_render_dist = DBL_MAX);
    Vector3d screen_to_viewport(const Vector2i16& screen_pos) const;

    std::pair<double,const Sphere*> closest_intersecting_sphere(const Line& ray);
    SDL_Color raytrace(const Vector3d& ray_dir);

    std::vector<Sphere> spheres;
    
};