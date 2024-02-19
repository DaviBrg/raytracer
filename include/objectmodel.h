#pragma once

#include "objectconcept.h"

namespace rtracer
{

template< typename T >
struct ObjectModel : public ObjectConcept
{
    
    ObjectModel(const T& t) : object(t) {}



    [[nodiscard]] auto Intersect(Ray const& ray) const noexcept -> std::optional<Intersection> override
    {
        return object.Intersect(ray);
    }

    [[nodiscard]] auto clone() const -> std::unique_ptr<ObjectConcept> override
    {
        return std::make_unique<ObjectModel>(object);
    }

private:
    T object;
};

}
