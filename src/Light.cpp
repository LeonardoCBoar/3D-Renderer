#include "Light.hpp"

double LightSource::diffuse_reflection(const Vector3d& normal_at_point, const Vector3d& light_dir) const
{
    const double intensity_ratio = light_dir.cos_between(normal_at_point);

    if(intensity_ratio<0)
        return 0.0;

    return this->intensity * intensity_ratio;
}

double LightSource::specular_reflection(const Vector3d& normal_at_point, const Vector3d& light_dir, 
                                        const Vector3d& camera_dir, const double specularity) const
{
    const Vector3d reflection_dir = (normal_at_point*2) * normal_at_point.dot(light_dir) - light_dir;

    const double intensity_ratio = pow(reflection_dir.cos_between(camera_dir),specularity);

    if(intensity_ratio<0)
        return 0.0;
    
    return this->intensity * intensity_ratio;
}


PointLight::PointLight(const double intensity, const Vector3d& origin)
    :LightSource{intensity},origin{origin}
{
    
}

double PointLight::intensity_at_point(const Vector3d& point,const Vector3d& normal_at_point,
                                      const Vector3d& camera_dir, const double specularity) const
{
    const Vector3d light_dir = this->origin - point;
    return LightSource::diffuse_reflection(normal_at_point,light_dir) +
           LightSource::specular_reflection(normal_at_point,light_dir,camera_dir,specularity);
}


DirectionalLight::DirectionalLight(const double intensity, const Vector3d& direction)
    :LightSource{intensity},direction{direction}
{

}

double DirectionalLight::intensity_at_point(const Vector3d& normal_at_point,
                                            const Vector3d& camera_dir, const double specularity) const
{
    return LightSource::diffuse_reflection(normal_at_point, this->direction) +
           LightSource::specular_reflection(normal_at_point,this->direction,camera_dir,specularity);
}



double SceneLight::total_intensity(const Vector3d& point,const Vector3d& normal_at_point,
                                   const Vector3d& camera_dir, const double specularity) const
{
    double intensity_at_point = ambient_light;

    for(const auto& point_light : point_lights)
    {
        intensity_at_point += point_light.intensity_at_point(point,normal_at_point,camera_dir,specularity);
    }

    for(const auto& directional_light : directional_lights)
    {
        intensity_at_point += directional_light.intensity_at_point(normal_at_point,camera_dir,specularity);
    }

    return intensity_at_point;
}