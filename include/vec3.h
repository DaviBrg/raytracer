
#pragma once

#include <cmath>
#include <numeric>
#include <iostream>

#include "rtincludes.h"

namespace rtracer
{

struct vec3;
rtfloat dot(vec3 const& lhs, vec3 const& rhs);

using color3 = vec3;
using point3 = vec3;

struct vec3
{
    vec3():
        x{0.0}, y{0.0}, z{0.0} {};

    vec3(rtfloat x, rtfloat y, rtfloat z):
        x{x}, y{y}, z{z} {};


    vec3& operator-()
    {
        x=-x;
        y=-y;
        z=-z;
        return *this;
    }

    vec3 operator-() const 
    {
        auto copy = *this;
        copy.x=-x;
        copy.y=-y;
        copy.z=-z;
        return copy;
    }

    vec3& operator+=(vec3 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec3& operator-=(vec3 const& other)
    {
        vec3 copy = other;
        return (*this)+=(-copy);
    }

    vec3& operator*=(rtfloat value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    vec3& operator/=(rtfloat value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    rtfloat length() const
    {
        return sqrt(dot(*this, *this));
    }

    vec3 normalize() const
    {
        rtfloat len = length();
        return {x/len, y/len, z/len};
    }

    rtfloat x,y,z;
};

struct Material
{
    color3 ambient;
    color3 diffuse;
    color3 specular;
};

inline std::ostream& operator<<(std::ostream& out, vec3 const& vec)
{
    return out << vec.x << ' ' << vec.y << ' ' << vec.z;
}

inline bool operator==(vec3 const& lhs, vec3 const& rhs)
{
    return (std::abs(lhs.x - rhs.x) < std::numeric_limits<rtfloat>::epsilon()) &&
           (std::abs(lhs.y - rhs.y) < std::numeric_limits<rtfloat>::epsilon()) &&
           (std::abs(lhs.z - rhs.z) < std::numeric_limits<rtfloat>::epsilon());
}

inline vec3 operator+(vec3 const& lhs, vec3 const& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

inline vec3 operator-(vec3 const& lhs, vec3 const& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

inline vec3 operator*(vec3 const& lhs, vec3 const& rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

inline vec3 operator*(vec3 const& vec, rtfloat value)
{
    return {vec.x * value, vec.y * value, vec.z * value};
}

inline vec3 operator*(rtfloat value, vec3 const& vec)
{
    return vec*value;
}

inline vec3 operator/(vec3 const& vec, rtfloat value)
{
    return {vec.x / value, vec.y / value, vec.z / value};
}

inline vec3 cross(vec3 const& lhs, vec3 const& rhs)
{
    return {lhs.y*rhs.z - lhs.z*rhs.y,
            lhs.z*rhs.x - lhs.x*rhs.z,
            lhs.x*rhs.y - lhs.y*rhs.x};
}

inline rtfloat dot(vec3 const& lhs, vec3 const& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

inline color3 rgbColor(uint8_t r, uint8_t g, uint8_t b)
{
    return color3{static_cast<rtfloat>(r)/255.0, static_cast<rtfloat>(g)/255.0, static_cast<rtfloat>(b)/255.0};
}

}





