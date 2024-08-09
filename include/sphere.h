#pragma once

#include <optional>

#include "intersection.h"
#include "ray.h"
#include "rtincludes.h"

namespace rtracer
{

struct Sphere {

    Sphere(point3 center, rtfloat radius, Material material);

    [[nodiscard]] auto intersect(Ray const& ray) const noexcept -> std::optional<Intersection>;

    [[nodiscard]] auto center() const noexcept -> point3 
    {
        return _center;
    }

    [[nodiscard]] auto radius() const noexcept -> rtfloat 
    {
        return _radius;
    }

    [[nodiscard]] auto material() const noexcept -> Material
    {
        return _material;
    }

private:
    point3 _center;
    rtfloat _radius;
    Material _material;

};

}