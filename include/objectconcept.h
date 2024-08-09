#pragma once

#include "ray.h"

#include <memory>
#include <optional>

#include "intersection.h"
#include "rtincludes.h"

namespace rtracer
{

struct ObjectConcept
{
    [[nodiscard]] virtual auto intersect(Ray const& ray) const noexcept -> std::optional<Intersection> = 0;

    [[nodiscard]] virtual auto clone() const -> std::unique_ptr<ObjectConcept> = 0;

    [[nodiscard]] virtual auto material() const noexcept -> Material = 0;

    virtual ~ObjectConcept() = default;
};

}