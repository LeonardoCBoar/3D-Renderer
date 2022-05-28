#pragma once

#include <math.h>
#include <iostream>
#include <ostream>



template<class NumberT>
class Vector3
{
public:
    NumberT x = 0;
    NumberT y = 0;
    NumberT z = 0;

    Vector3()
    {

    }

    Vector3(const NumberT x,const NumberT y, const NumberT z)
    : x{x},y{y},z{z}
    {

    }

    template<typename OtherNumberT>
    bool operator == (const Vector3<OtherNumberT>& other) const
    {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    Vector3<NumberT> operator + (const Vector3<NumberT>& other) const
    {
        return Vector3<NumberT>(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vector3<NumberT> operator - (const Vector3<NumberT>& other) const
    {
        return Vector3<NumberT>(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    Vector3<NumberT> operator - () const
    {
        return Vector3<NumberT>(-this->x,-this->y,-this->z);
    }

    Vector3<NumberT> operator * (const Vector3<NumberT>& other) const
    {
        return Vector3<NumberT>(this->x * other.x, this->y * other.y, this->z * other.z);
    }

    template<typename OtherNumberT>
    Vector3<NumberT> operator * (const OtherNumberT& number) const
    {
        return Vector3<NumberT>(this->x * number, this->y * number, this->z * number);
    }

    Vector3<NumberT> operator / (const Vector3<NumberT>& other) const
    {
        return Vector3<NumberT>(this->x / other.x, this->y / other.y, this->z / other.z);
    }

    template<typename OtherNumberT>
    Vector3<NumberT> operator / (const OtherNumberT& number) const
    {
        return Vector3<NumberT>(this->x / number, this->y / number, this->z / number);
    }

    NumberT dot(const Vector3<NumberT>& other) const
    {
        return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
    }

    double cos_between(const Vector3<NumberT>& other) const
    {
        return this->dot(other)/(this->length() * other.length());
    }

    double angle_to(const Vector3<NumberT>& other) const
    {
        return acos(this->cos_between(other));
    }

    double distance_to(const Vector3<NumberT>& other) const
    {
        return (*this-other).length();
    }


    double length() const
    {
        return sqrt( (this->x*this->x) + (this->y*this->y) + (this->z*this->z) );
    }
};

template<class NumberT>
class Vector2
{
public:
    NumberT x = 0;
    NumberT y = 0;

    Vector2()
    {

    }

    Vector2(const NumberT x,const NumberT y)
    : x{x},y{y}
    {

    }


    Vector2<NumberT> operator + (const Vector2<NumberT>& other) const
    {
        return Vector2<NumberT>(this->x + other.x, this->y + other.y);
    }

    Vector2<NumberT> operator - (const Vector2<NumberT>& other) const
    {
        return Vector2<NumberT>(this->x - other.x, this->y - other.y);
    }

    Vector2<NumberT> operator * (const Vector2<NumberT>& other) const
    {
        return Vector2<NumberT>(this->x * other.x, this->y * other.y);
    }

    Vector2<NumberT> operator / (const Vector2<NumberT>& other) const
    {
        return Vector2<NumberT>(this->x / other.x, this->y / other.y);
    }

    NumberT dot(const Vector2<NumberT>& other) const
    {
        return (this->x * other.x) + (this->y * other.y) ;
    }

    float length() const
    {
        return sqrt( (this->x*this->x) + (this->y*this->y) );
    }
};

template<class NumberT>
std::ostream& operator <<(std::ostream& ostream, const Vector3<NumberT>& vector)
{
    return ostream << '(' << vector.x << ',' << vector.y << ',' << vector.z << ')';
}

template<class NumberT>
std::ostream& operator <<(std::ostream& ostream, const Vector2<NumberT>& vector)
{
    return ostream << '(' << vector.x << ',' << vector.y << ')';
}

using Vector3u16 = Vector3<uint16_t>;
using Vector3u32 = Vector3<uint32_t>;
using Vector3i16 = Vector3<int16_t>;
using Vector3i32 = Vector3<int16_t>;
using Vector3d   = Vector3<double>;


using Vector2u16 = Vector2<uint16_t>;
using Vector2u32 = Vector2<uint32_t>;
using Vector2i16 = Vector2<int16_t>;
using Vector2i32 = Vector2<int16_t>;
using Vector2d   = Vector2<double>;

namespace Vectors
{
    inline Vector3d ZERO{0,0,0};
    inline Vector3d ONE {1,1,1};
}