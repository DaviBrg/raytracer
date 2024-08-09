#pragma once

#include "objectconcept.h"

namespace rtracer
{

template< typename T >
struct ObjectModel : public ObjectConcept
{
    
    ObjectModel(const T& t) : object(t) {}

    [[nodiscard]] auto intersect(Ray const& ray) const noexcept -> std::optional<Intersection> override
    {
        return object.intersect(ray);
    }

    [[nodiscard]] auto clone() const -> std::unique_ptr<ObjectConcept> override
    {
        return std::make_unique<ObjectModel>(object);
    }

    [[nodiscard]] auto material() const noexcept -> Material
    {
        return object.material();
    }

private:
    T object;
};

}
