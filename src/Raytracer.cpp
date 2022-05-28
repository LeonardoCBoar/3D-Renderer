#include "Raytracer.hpp"

Raytracer::Raytracer(const Vector3d& camera_pos,const Vector2u16& viewport_size,const Vector2u16& screen_size,
                     const double viewport_dist,std::vector<Sphere> spheres,
                     const double min_render_dist, const double max_render_dist)
    :camera_pos{camera_pos}, viewport_size{viewport_size}, screen_size{screen_size},
     viewport_dist{viewport_dist}, spheres{spheres},
     min_render_dist{min_render_dist}, max_render_dist{max_render_dist}
{

}

Vector3d Raytracer::screen_to_viewport(const Vector2i16& screen_pos) const
{
    return Vector3d
    {
        screen_pos.x * (double)this->viewport_size.x/(double)this->screen_size.x,
        screen_pos.y * (double)this->viewport_size.y/(double)this->screen_size.y,
        this->viewport_dist
    };
}

std::pair<double,const Sphere*> Raytracer::closest_intersecting_sphere(const Line& ray)
{

    double closest_sphere_dist = this->max_render_dist;
    const Sphere* closest_sphere = nullptr;

    for(const auto& sphere : this->spheres)
    {
        const DoublePair intersection_dists = sphere.ray_intersection_dists(ray);
        
        if(intersection_dists.first.has_value())
        {

            const double dist1 = intersection_dists.first.value();
            if(dist1 > this->min_render_dist && dist1 < this->max_render_dist && dist1 < closest_sphere_dist)
            {
                closest_sphere = &sphere;
                closest_sphere_dist = dist1;
            }
        }
        if(intersection_dists.second.has_value())
        {
            const double dist2 = intersection_dists.second.value();
            if(dist2 > this->min_render_dist && dist2 < this->max_render_dist && dist2 < closest_sphere_dist)
            {
                closest_sphere = &sphere;
                closest_sphere_dist = dist2;
            }
        }
    }

    return std::pair<double,const Sphere*>{closest_sphere_dist,closest_sphere};
}

SDL_Color Raytracer::raytrace(const Vector3d& ray_dir)
{
    const Line ray{this->camera_pos,ray_dir};

    const std::pair<double,const Sphere*> intersection_data = closest_intersecting_sphere(ray);
    const Sphere* closest_sphere = intersection_data.second;
    const double  intersectin_dist = intersection_data.first;
    if(closest_sphere != nullptr)
    {
        SDL_Color point_color = closest_sphere->color;
        
        const Vector3d intersection_point = ray.point_at(intersectin_dist);
        /*std::cout << intersectin_dist << std::endl;
        std::cout << intersection_point << std::endl;
        std::cout << closest_sphere->center.distance_to(intersection_point);*/
        const Vector3d sphere_normal_at_point = closest_sphere->normal_at_point(intersection_point);

        light.apply_all_lights(intersection_point,sphere_normal_at_point,point_color);
        return point_color; 
    }
    else
        return SDL_Color{0,0,0,255};
}
