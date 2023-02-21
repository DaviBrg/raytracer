
#pragma once

#include <cmath>
#include <numeric>
#include <iostream>

namespace rtracer
{

struct vec3;
double dot(vec3 const& lhs, vec3 const& rhs);

using color3 = vec3;
using point3 = vec3;

struct vec3
{
    vec3(double x, double y, double z):
        x(x),y(y),z(z) {};


    vec3& operator-()
    {
        x=-x;
        y=-y;
        z=-z;
        return *this;
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

    vec3& operator*=(double value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    vec3& operator/=(double value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    double length() const
    {
        return sqrt(dot(*this, *this));
    }

    vec3 normalize() const
    {
        double len = length();
        return {x/len, y/len, z/len};
    }

    double x,y,z;
};


inline std::ostream& operator<<(std::ostream& out, vec3 const& vec)
{
    return out << vec.x << ' ' << vec.y << ' ' << vec.z;
}

inline bool operator==(vec3 const& lhs, vec3 const& rhs)
{
    return (std::abs(lhs.x - rhs.x) < std::numeric_limits<double>::epsilon()) &&
           (std::abs(lhs.y - rhs.y) < std::numeric_limits<double>::epsilon()) &&
           (std::abs(lhs.z - rhs.z) < std::numeric_limits<double>::epsilon());
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

inline vec3 operator*(vec3 const& vec, double value)
{
    return {vec.x * value, vec.y * value, vec.z * value};
}

inline vec3 operator*(double value, vec3 const& vec)
{
    return vec*value;
}

inline vec3 operator/(vec3 const& vec, double value)
{
    return {vec.x / value, vec.y / value, vec.z / value};
}

inline vec3 cross(vec3 const& lhs, vec3 const& rhs)
{
    return {lhs.y*rhs.z - lhs.z*rhs.y,
            lhs.z*rhs.x - lhs.x*rhs.z,
            lhs.x*rhs.y - lhs.y*rhs.x};
}

inline double dot(vec3 const& lhs, vec3 const& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

}





