#pragma once

#include "Vector.hpp"
#include "Utils.hpp"

#include <optional>
#include <utility>
#include <SDL_pixels.h>

using DoubleOpt    = std::optional<double>;
using DoublePair   = std::pair<std::optional<double>  ,std::optional<double>>;
using Vector3dPair = std::pair<std::optional<Vector3d>, std::optional<Vector3d>>;


inline DoublePair quadratic_roots(const double a, const double b, const double c);

constexpr double DOUBLE_PRECISION5 = 1.0/100000.0;
inline bool double_equal (const double a,const double b);
inline bool double_round5(const double d);

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

    bool contains(const Vector3d& point) const;
    Vector3d normal_at_point(const Vector3d& point) const;
    
    Vector3dPair ray_intersection_points(const Line& ray) const;
    DoublePair   ray_intersection_dists (const Line& ray) const;

    bool operator ==(const Sphere& other);
};

inline std::ostream& operator <<(std::ostream& ostream, const Sphere& sphere)
{
    return ostream << "C:" << sphere.center << " R:" << sphere.radius;
}

inline std::ostream& operator <<(std::ostream& ostream, const Line& line)
{
    return ostream << "O:" << line.origin << " D:" << line.direction;
}
