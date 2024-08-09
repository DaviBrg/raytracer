#pragma once

#include "vec3.h"

#include <vector>

namespace rtracer
{

struct Ray
{

    Ray(const point3& origin, const vec3& direction):
    _origin{origin}, _direction{direction} {};

    [[nodiscard]] auto origin() const noexcept -> const point3&
    {
        return _origin;
    }

    [[nodiscard]] auto direction() const noexcept -> const vec3&
    {
        return _direction;
    }

private:
    point3 _origin;
    vec3 _direction;
    
};

using Rays = std::vector<Ray>;

}