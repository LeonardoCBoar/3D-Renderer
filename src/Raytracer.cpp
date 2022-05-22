#include "Raytracer.hpp"

Raytracer::Raytracer(const Vector3d& camera_pos,const Vector2u16& viewport_size,const Vector2u16& screen_size,const double viewport_dist,
                     const double min_render_dist, const double max_render_dist)
    :camera_pos{camera_pos}, viewport_size{viewport_size}, screen_size{screen_size}, viewport_dist{viewport_dist},
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

SDL_Color Raytracer::raytrace(const Vector3d& ray_dir)
{
    const Line ray{this->camera_pos,ray_dir};

    double closest_sphere_dist = max_render_dist;
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

    if(closest_sphere != nullptr)
        return closest_sphere->color;
    else
        return SDL_Color{0,0,0,255};
}
