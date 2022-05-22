#pragma once

#include "Vector.hpp"

#include <optional>
#include <utility>
#include <SDL_pixels.h>

using DoublePair   = std::pair<std::optional<double>  ,std::optional<double>>;
using Vector3dPair = std::pair<std::optional<Vector3d>, std::optional<Vector3d>>;


inline DoublePair quadratic_roots(const double a, const double b, const double c);

class Line
{
public:
    Vector3d origin;
    Vector3d direction;

    Vector3d point_at(const double direction_multiplier) const;
};

class Sphere
{
public:
    Vector3d center;
    double radius;
    SDL_Color color;
    
    Vector3dPair ray_intersection_points(const Line& ray) const;
    DoublePair   ray_intersection_dists (const Line& ray) const;
};
