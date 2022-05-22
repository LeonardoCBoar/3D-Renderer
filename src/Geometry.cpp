#include "Geometry.hpp"

Vector3d Line::point_at(const double direction_multiplier) const
{
    return this->origin + this->direction * direction_multiplier;
}

DoublePair quadratic_roots(const double a, const double b, const double c)
{
    const double delta = b*b - 4*a*c;
    
    if(delta<0)
        return DoublePair{std::nullopt,std::nullopt};
    
    const double delta_sqrt = sqrt(delta);

    double root1 = -b + delta_sqrt/(2*a);
    double root2 = -b - delta_sqrt/(2*a);

    /*if(should_log)
    {
        std::cout << "A: " << a;
        std::cout << "  B: " << b;
        std::cout << "  C: " << c;
        std::cout << std::endl;
        std::cout << "Roots: " << root1 << " | " << root2 << std::endl << std::endl;
    }*/

    if(delta==0)
        return DoublePair{root1,std::nullopt};
    else
        return DoublePair{root1,root2};
}

DoublePair Sphere::ray_intersection_dists(const Line& ray) const
{
    const Vector3d origin_to_sphere_center = ray.origin - this->center;
    const double radius = this->radius;
    bool should_log = false;

    const double a = ray.direction.dot(ray.direction);
    const double b = 2*origin_to_sphere_center.dot(ray.direction);
    const double c = origin_to_sphere_center.dot(origin_to_sphere_center) - radius*radius;

    return quadratic_roots(a,b,c);
    
}

Vector3dPair Sphere::ray_intersection_points(const Line& ray) const
{
    const DoublePair intersection_dists = ray_intersection_dists(ray);

    if(!intersection_dists.first.has_value())
        return Vector3dPair{std::nullopt,std::nullopt};

    const Vector3d point1 = ray.point_at(intersection_dists.first.value());

    if(!intersection_dists.second.has_value())
        return Vector3dPair{point1,std::nullopt};

    const Vector3d point2 = ray.point_at(intersection_dists.second.value());
    
    return Vector3dPair{point1,point2};

}

