#pragma once

#include <vector>

#include <SDL_pixels.h>

#include "Vector.hpp"

class LightSource
{
public:
    double intensity;
    double diffuse_reflection(const Vector3d& normal_at_point, const Vector3d& light_dir) const;
};


class PointLight : public LightSource
{
public:
    Vector3d origin;

    PointLight(const double intensity,const Vector3d& origin);
    double intensity_at_point(const Vector3d& point,const Vector3d& normal_at_point) const;
};


class DirectionalLight : LightSource
{
public:
    Vector3d direction;

    DirectionalLight(const double intensity, const Vector3d& direction);

    double intensity_at_point(const Vector3d& normal_at_point) const;
};


class SceneLight
{

    double ambient_light = 0.2;
    
    std::vector<PointLight> point_lights
    {
        PointLight
        {
            0.6,
            Vector3d{2,1,0}
        },
    };

    std::vector<DirectionalLight> directional_lights
    {
        DirectionalLight
        {
            0.2,
            Vector3d{1,4,4}
        },
    };

public:
    void apply_all_lights(const Vector3d& point,const Vector3d& normal_at_point,SDL_Color& point_color) const;
};