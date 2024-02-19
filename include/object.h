#pragma once

#include "objectmodel.h"

namespace rtracer
{

struct Object
{
    template <class T>
    Object(T&& object):
    _object(std::make_unique<ObjectModel<T>>(std::forward<T>(object))){}
    

    Object(Object const& other);
    auto operator=(Object const& other) -> Object &;

    [[nodiscard]] auto Intersect(Ray const& ray) const noexcept -> std::optional<Intersection>;

private:
    std::unique_ptr<ObjectConcept> _object;
};

}