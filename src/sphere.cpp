#include "sphere.h"

namespace rtracer
{

Sphere::Sphere(point3 center, rtfloat radius, Material material):
    _center{center}, _radius{radius}, _material{material} {}

auto Sphere::intersect(Ray const &ray) const noexcept -> std::optional<Intersection>
{
    const vec3 oc = _center - ray.origin();
    const rtfloat a = dot(ray.direction(), ray.direction());
    const rtfloat b = -2*dot(ray.direction(), oc);
    const rtfloat c = dot(oc, oc) - (_radius*_radius);
    const rtfloat delta = (b*b) - (4*a*c);

    if (delta < 0.0)
    {
        return std::nullopt;
    }

    const rtfloat t1 = std::max((-b + sqrt(delta))/(2*a), 0.0);
    const rtfloat t2 = std::max((-b - sqrt(delta))/(2*a), 0.0);
    const rtfloat intersetcT = std::min(t1, t2);

    if (intersetcT > 0.0)
    {
        const point3 intersectPoint = ray.origin() + (ray.direction()*intersetcT);
        const vec3 intersectNormal = (intersectPoint - _center).normalize();
        return std::optional<Intersection>(Intersection{intersetcT, intersectNormal});
        
    } else
    {
        return std::nullopt;
    }
}

}