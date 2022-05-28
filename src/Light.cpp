#include "Light.hpp"

double LightSource::diffuse_reflection(const Vector3d& normal_at_point, const Vector3d& light_dir) const
{
    //const double intensity_ratio = light_dir.cos_between(normal_at_point);
    const double intensity_ratio = (normal_at_point.dot(light_dir)) / (normal_at_point.length()*light_dir.length());

    if(intensity_ratio<0)
        return 0.0;

    return this->intensity * intensity_ratio;
}


PointLight::PointLight(const double intensity, const Vector3d& origin)
    :LightSource{intensity},origin{origin}
{
    
}

double PointLight::intensity_at_point(const Vector3d& point,const Vector3d& normal_at_point) const
{
    const Vector3d light_dir = this->origin - point ;
    return LightSource::diffuse_reflection(normal_at_point,light_dir);
}


DirectionalLight::DirectionalLight(const double intensity, const Vector3d& direction)
    :LightSource{intensity},direction{direction}
{

}

double DirectionalLight::intensity_at_point(const Vector3d& normal_at_point) const
{
    return LightSource::diffuse_reflection(normal_at_point, this->direction);
}



void SceneLight::apply_all_lights(const Vector3d& point,const Vector3d& normal_at_point,SDL_Color& point_color) const
{
    double intensity_at_point = ambient_light;

    for(const auto& point_light : point_lights)
    {
        intensity_at_point += point_light.intensity_at_point(point,normal_at_point);
    }

    for(const auto& directional_light : directional_lights)
    {
        intensity_at_point += directional_light.intensity_at_point(normal_at_point);
    }

    point_color.r *= intensity_at_point;
    point_color.g *= intensity_at_point;
    point_color.b *= intensity_at_point;

}