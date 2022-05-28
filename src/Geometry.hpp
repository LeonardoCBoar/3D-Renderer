#pragma once

#include "Vector.hpp"
#include "Utils.hpp"
#include "Color.hpp"

#include <optional>
#include <utility>

using DoubleOpt    = std::optional<double>;
using DoublePair   = std::pair<std::optional<double>  ,std::optional<double>>;
using Vector3dPair = std::pair<std::optional<Vector3d>, std::optional<Vector3d>>;



inline bool double_equal(const double a, const double b, const int precision = 5)
{
    return abs(a-b) < 1/pow(10,precision);
}
inline double double_round(const double d, const int precision = 5)
{
    const double precision_mult = pow(10,precision);
    return round(d*precision_mult)/precision_mult;
}

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
    Color color;
    int shine_level;

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
