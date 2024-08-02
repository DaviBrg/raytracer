#pragma once

#include "ray.h"

#include <memory>
#include <optional>

namespace rtracer
{

struct Intersection
{
    rtfloat t = {};
    vec3 normal = {};
};

struct ObjectConcept
{
    [[nodiscard]] virtual auto Intersect(Ray const& ray) const noexcept -> std::optional<Intersection> = 0;

    [[nodiscard]] virtual auto clone() const -> std::unique_ptr<ObjectConcept> = 0;

    virtual ~ObjectConcept() = default;
};

}