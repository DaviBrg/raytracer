#pragma once

#include "ray.h"

namespace rtracer
{

using Intersection = std::pair<rtfloat,vec3>;

struct Object
{

    [[nodiscard]] virtual auto Intersect(Ray const& ray) const noexcept -> Intersection = 0;

    virtual ~Object() = default;

};

}