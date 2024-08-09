#include "object.h"

namespace rtracer
{

Object::Object(Object const& other):
    _object{other._object->clone()} {}

auto Object::operator=(Object const& other) -> Object &
{
    if (this != &other)
    {
        _object = other._object->clone();
    }
    return *this;
}

auto Object::intersect(Ray const& ray) const noexcept -> std::optional<Intersection>
{
    return _object->intersect(ray);
}

auto Object::material() const noexcept -> Material
{
    return _object->material();;
}
}