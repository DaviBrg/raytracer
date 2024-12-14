#include "renderer.h"

#include <algorithm>
#include <cassert>
#include <thread>
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
    const auto pixelRays = _camera.createRays();
    assert(_image.size() == pixelRays.size());

    const rtsize numThreads = std::thread::hardware_concurrency();

    auto parallelRender = [this,&pixelRays,numThreads](rtsize threadIndex)
    {
        for (;threadIndex < pixelRays.size(); threadIndex += numThreads)
        {
            renderPixelRay(pixelRays[threadIndex]);    
        }
    };

    std::vector<std::jthread> threads;

    for (rtsize threadIndex = 0; threadIndex < numThreads; ++threadIndex) {
        threads.emplace_back([&parallelRender,threadIndex]()
        {
            parallelRender(threadIndex);
        });
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

auto Renderer::renderPixelRay(PixelRay const &pixelRay) const -> void
{
    auto pixelIndex = pixelRay.pixel;
        auto [ptrObj, optIntersection] = closestIntersection(pixelRay.ray);
        if (optIntersection.has_value())
        {
            auto intersection = optIntersection.value();
            auto intersectionPoint = pixelRay.ray.origin() + pixelRay.ray.direction()*intersection.t;
            if (canReachLightSource(intersectionPoint))
            {
                renderPhong(pixelIndex, pixelRay.ray, intersection, ptrObj->material());
            }
            else
            {
                renderAmbient(pixelIndex, ptrObj->material());
            }
        }
        else
        {
            renderBackground(pixelIndex);
        }
}

auto Renderer::renderPhong(rtsize pixelIndex, Ray const &ray, Intersection const &intersection, Material const &material) const -> void
{
    auto toLight = (_settings.lightPosition - (ray.origin() + ray.direction()*intersection.t)).normalize();
    auto diffuseComponenet = dot(intersection.normal, toLight);
    if (diffuseComponenet < 0) diffuseComponenet = 0;
    _image[pixelIndex] = material.diffuse*diffuseComponenet + (AMBIENT_COMPONENT*material.ambient);
}

auto Renderer::renderAmbient(rtsize pixelIndex, Material const& material) const -> void
{
    _image[pixelIndex] = (AMBIENT_COMPONENT*material.ambient);
}

auto Renderer::renderBackground(rtsize pixelIndex) const -> void
{
    _image[pixelIndex] = _settings.backgroundColor;
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