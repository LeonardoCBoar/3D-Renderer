#include <math.h>

#include <gtest/gtest.h>

#include "../src/Geometry.hpp"
#include "../src/Light.hpp"
#include "../src/Vector.hpp"
#include "../src/Raytracer.hpp"
#include "../src/Color.hpp"

TEST(GeometryTest, DoubleOperations)
{
    EXPECT_EQ(double_round(5.0000000000001),5);
    EXPECT_EQ(double_round(0.000001),0);
    EXPECT_EQ(double_round(0.00001),0.00001);

    EXPECT_TRUE(double_equal(5.0000000000001,5));
    EXPECT_TRUE(double_equal(0.000001,0));
    EXPECT_FALSE(double_equal(0.00001,0));

}

TEST(GeometryTest, QuadraticRoots)
{
    const DoublePair result1 = quadratic_roots(1,6,5);
    EXPECT_EQ(result1.first.value() , -1 );
    EXPECT_EQ(result1.second.value(), -5 );

    const DoublePair result2 = quadratic_roots(-2,1,3);
    EXPECT_EQ(result2.first.value() , -1);
    EXPECT_EQ(result2.second.value(), 1.5);

    const DoublePair result3 = quadratic_roots(-4,8,0);
    EXPECT_EQ(result3.first.value() , 0);
    EXPECT_EQ(result3.second.value(), 2);

    const DoublePair result4 = quadratic_roots(1,0,0);
    EXPECT_EQ(result4.first.value() , 0);
    EXPECT_FALSE(result4.second.has_value());
}

TEST(GeometryTest, SphereTest)
{

    Sphere sphere1{Vector3d{0,0,0},5};
    Vector3d point1{5,0,0};
    Vector3d point2{0,-5,0};
    Vector3d point3{0,1,5};
    Vector3d point4{0,0,0};
    Vector3d point5{2,2,2};
    Vector3d point6{5,5,5};
    Vector3d point7{8,8,8};
    Vector3d point8{-600,600,0};

    //Contains
    EXPECT_TRUE(sphere1.contains(point1));
    EXPECT_TRUE(sphere1.contains(point2));
    EXPECT_FALSE(sphere1.contains(point3));
    EXPECT_TRUE(sphere1.contains(point4));
    EXPECT_TRUE(sphere1.contains(point5));
    EXPECT_FALSE(sphere1.contains(point6));
    EXPECT_FALSE(sphere1.contains(point7));
    EXPECT_FALSE(sphere1.contains(point8));

    //Normal at point
    EXPECT_EQ(Vector3d(1,0,0),sphere1.normal_at_point(point1));
    EXPECT_EQ(Vector3d(0,-1,0),sphere1.normal_at_point(point2));
    EXPECT_EQ(Vector3d(3,4,0)/5,sphere1.normal_at_point(Vector3d(3,4,0)));

}



TEST(GeometryTest, SphereIntersections)
{
    Sphere sphere1{Vector3d{2,2,2},4};
    Line ray1
    {
        Vector3d{2,6,0},
        Vector3d{0,0,1}
    };
    
    DoublePair intersection1 = sphere1.ray_intersection_dists(ray1);
    EXPECT_TRUE(intersection1.first.has_value());
    EXPECT_FALSE(intersection1.second.has_value());
    EXPECT_EQ(intersection1.first.value(),2);

    EXPECT_EQ(ray1.point_at(intersection1.first.value()), Vector3d(2,6,2) );
}

TEST(GeometryTest, LineTest)
{
    
}

TEST(RaytracerTests,ClosestSphere)
{
    std::vector<Sphere> test_spheres
    {
        Sphere
        {
            Vector3d(0,0,3),
            1.5,
            Color::Black
        },
        
        Sphere
        {
            Vector3d(0,0,1),
            1,
            Color::Black
        },
        Sphere
        {
            Vector3d(0,0,5),
            5,
            Color::Black
        }
    };
    Raytracer raytracer{Vectors::ZERO,Vector2u16(1,1),Vector2u16(1,1),1,test_spheres};

    Line z_ray
    {
        Vectors::ZERO,
        Vector3d(0,0,1),
    };

    std::pair<double,const Sphere*> intersection_data = raytracer.closest_intersecting_sphere(z_ray);
    EXPECT_EQ(intersection_data.second->center,test_spheres[0].center);
    EXPECT_EQ(intersection_data.first,1.5);


    std::vector<Sphere> test_spheres2
    {
        Sphere
        {
            Vector3d(0,55,0),
            1,
            Color::Black
        }, 
        Sphere
        {
            Vector3d(0,1,0),
            1,
            Color::Black
        },
        Sphere
        {
            Vector3d(0,55,0),
            5,
            Color::Black
        }
    };

    Raytracer raytracer2{Vectors::ZERO,Vector2u16(1,1),Vector2u16(1,1),1,test_spheres2};

    Line y_ray
    {
        Vectors::ZERO,
        Vector3d(0,1,0)
    };



    EXPECT_EQ(raytracer2.closest_intersecting_sphere(y_ray).second->center,test_spheres2[1].center);
    
    std::vector<Sphere> test_spheres3
    {
        Sphere
        {
            Vector3d(0,5,5),
            1,
            Color::Black 
        }, 
        Sphere
        {
            Vector3d(0,-5,5),
            1,
            Color::Black
        },
        Sphere
        {
            Vector3d(0,-3,3),
            1,
            Color::Black
        },
        Sphere
        {
            Vector3d(0,0,1),
            0.1,
            Color::Black
        }
    };

    Raytracer raytracer3{Vectors::ZERO,Vector2u16(1,1),Vector2u16(1,1),1,test_spheres3};

    Line inclined_ray 
    {
        Vectors::ZERO,
        Vector3d(0,-1,1)
    };


    EXPECT_EQ(raytracer3.closest_intersecting_sphere(inclined_ray).second->center,test_spheres3[2].center);
}



TEST(Vector3Test, Operators)
{
    Vector3d vec1d{1,1,1};
    Vector3d vec2d{2,2,2};
    Vector3d vec3d{1,1,1};
    Vector3d vec4d{3,3,3};
    Vector3d vec5d{-1,-1,-1};
    Vector3d vec6d{-2,-2,-2};
    Vector3d vec7d{0,0,0};
    Vector3d vec8d{6,6,6};
    Vector3d vec9d{-5,-5,-5};
    Vector3d vec10d{1.5,1.5,1.5};

    EXPECT_FALSE(vec1d == vec2d);
    EXPECT_TRUE(vec1d == vec3d);

    Vector3i16 vec1i{1,1,1};
    Vector3i32 vec2i{1,1,1};
    
    EXPECT_TRUE(vec1d == vec1i);
    EXPECT_TRUE(vec1d == vec2i);

    EXPECT_EQ(vec1d+vec2d,vec4d);
    EXPECT_EQ(vec1d-vec2d,vec5d);
    EXPECT_EQ(vec3d-vec3d,vec7d);
    EXPECT_EQ(vec5d,-vec1d);
    EXPECT_EQ(vec2d*vec4d,vec8d);
    EXPECT_EQ(vec1d*2,vec2d);
    EXPECT_EQ(vec1d*-5,vec9d);
    EXPECT_EQ(vec6d/2,vec5d);
    EXPECT_EQ(vec4d/vec2d,vec10d);
    EXPECT_EQ(vec4d/2,vec10d);
}

TEST(Vector3Test, Dot)
{
    Vector3d vec1d{1,1,1};
    Vector3d vec2d{2,2,2};
    Vector3d vec3d{2,2,-4};

    EXPECT_EQ(6,vec1d.dot(vec2d));
    EXPECT_EQ(0,vec1d.dot(vec3d));
}

TEST(Vector3Test, Length)
{
    Vector3d vec1d{3,4,0};
    EXPECT_EQ(5,vec1d.length());

    Vector3d vec2d{7,4,5};
    Vector3d vec3d{-7,4,-5};
    EXPECT_EQ(vec3d.length(), vec2d.length());
}

TEST(Vector3Test, DistanceTo)
{
    Vector3d vec1d{1,1,1};
    Vector3d vec2d{2,1,1};
    Vector3d vec3d{1,3,1};
    Vector3d vec4d{-7,1,1};
    Vector3d vec5d{1,1,1};

    EXPECT_EQ(1,vec1d.distance_to(vec2d));
    EXPECT_EQ(2,vec1d.distance_to(vec3d));
    EXPECT_EQ(8,vec1d.distance_to(vec4d));
    EXPECT_EQ(0,vec1d.distance_to(vec5d));
    EXPECT_EQ(9,vec2d.distance_to(vec4d));

    EXPECT_EQ(vec1d.distance_to(vec2d),vec2d.distance_to(vec1d));
    EXPECT_EQ(vec2d.distance_to(vec3d),vec3d.distance_to(vec2d));
    EXPECT_EQ(vec3d.distance_to(vec4d),vec3d.distance_to(vec4d));

    EXPECT_EQ(vec1d.distance_to(-vec1d),2*vec1d.length());

    EXPECT_NEAR(2.23,vec2d.distance_to(vec3d),0.01);
    EXPECT_NEAR(8.24,vec3d.distance_to(vec4d),0.01);


}

TEST(Vector3Test, AngleTo)
{
    Vector3d vec1d{4,5,7};
    Vector3d vec2d{16,6,8};

    EXPECT_NEAR(0.57,vec1d.angle_to(vec2d),0.01);
    EXPECT_NEAR(vec1d.angle_to(vec2d),vec2d.angle_to(vec1d),0.01);

    Vector3d vec3d{0,-1,0};
    Vector3d vec4d{-2,3,0};

    EXPECT_NEAR(2.55,vec3d.angle_to(vec4d),0.01);
}

TEST(Vector3dTest, CosBetween)
{
    Vector3d vec1d{0,-1,0};
    Vector3d vec2d{1,1,0};

    EXPECT_NEAR(-0.70,vec1d.cos_between(vec2d),0.01);
    EXPECT_NEAR(vec1d.cos_between(vec2d),vec2d.cos_between(vec1d),0.01);
}

TEST(LightTest, DiffuseReflection)
{
    LightSource light_source{0.6};

    Vector3d vec1d{13,1,1};
    Vector3d vec2d{2,2,2};

    EXPECT_NEAR(0.39,light_source.diffuse_reflection(vec1d,vec2d),0.1);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}