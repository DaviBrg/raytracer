#include "renderer.h"

#include <algorithm>
#include <cassert>
#include <tuple>

namespace rtracer
{

namespace
{

constexpr rtfloat AMBIENT_COMPONENT = 0.3;

Camera::Settings createCameraSettings(const Image& image, Renderer::Settings settings)
{
    return Camera::Settings
    {
        settings.viewportHeight,
        image.height(),
        static_cast<rtfloat>(image.width())/image.height(),
        settings.focalDistance,
        settings.eye,
        settings.at,
        vec3{0.0, 1.0, 0.0}
    };

}

}

Renderer::Renderer(Image &image, Settings settings) :
_image{image},
_settings{settings},
_camera{createCameraSettings(image, settings)} {}

auto Renderer::render() const -> void
{
    auto rays = _camera.createRays();
    assert(_image.size() == rays.size());

    for(rtsize i = 0; i < _image.size(); ++i)
    {
        Ray const& ray = rays.at(i);
        auto [ptrObj, optIntersection] = closestIntersection(ray);
        if (optIntersection.has_value())
        {
            auto intersection = optIntersection.value();
            auto intersectionPoint = ray.origin() + ray.direction()*intersection.t;
            if (canReachLightSource(intersectionPoint))
            {
                renderIntersection(i, ray, intersection, ptrObj->material());
            }
            else
            {
                _image[i] = (AMBIENT_COMPONENT*ptrObj->material().ambient);
            }
        }
        else
        {
            _image[i] = _settings.backgroundColor;
        }
    }
}

auto Renderer::updateRenderingSettings(Settings settings) -> void
{
    _settings = settings;
    _camera = Camera{createCameraSettings(_image, settings)};
}

auto Renderer::addObject(Object object) -> void
{
    _objects.emplace_back(std::move(object));
}

auto Renderer::renderIntersection(rtsize pixelIndex, Ray const& ray,  Intersection const &intersection, Material const& material) const -> void
{
    auto toLight = (_settings.lightPosition - (ray.origin() + ray.direction()*intersection.t)).normalize();
    auto diffuseComponenet = dot(intersection.normal, toLight);
    if (diffuseComponenet < 0) diffuseComponenet = 0;
    _image[pixelIndex] = material.diffuse*diffuseComponenet + (AMBIENT_COMPONENT*material.ambient);
}

auto Renderer::closestIntersection(Ray const& ray) const -> ObjectIntersection
{
    std::vector<ObjectIntersection> intersections;

    std::transform
    (
        std::cbegin(_objects),
        std::cend(_objects),
        std::back_inserter(intersections),
        [&](Object const& obj) -> ObjectIntersection
        {
            return {&obj, obj.intersect(ray)};
        }
    );

    intersections.erase
    (
        std::remove_if
        (
            std::begin(intersections),
            std::end(intersections),
            [](ObjectIntersection const& objectIntersection)
                {
                    return !objectIntersection.second.has_value()  || (objectIntersection.second.value().t < 1.0);
                }
        ),
        std::end(intersections)
    );

    if (intersections.empty())
    {
        return {nullptr, std::nullopt};
    }

    auto minT = std::min_element
    (
        std::begin(intersections),
        std::end(intersections),
        [](std::pair<Object const*,std::optional<Intersection>> const& lhs, std::pair<Object const*,std::optional<Intersection>> const& rhs)
        {
            return lhs.second.value().t < rhs.second.value().t;
        }
    );

    return *minT;
}
auto Renderer::canReachLightSource(point3 intersection) const -> bool
{
    auto ray = Ray{intersection, _settings.lightPosition - intersection};

    for (auto const& obj : _objects)
    {
        auto intersectOpt = obj.intersect(ray);
        if (intersectOpt.has_value())
        {
            if (intersectOpt.value().t < 1.0)
            {
                return false;
            }
        }
    }
    return true;
}
}