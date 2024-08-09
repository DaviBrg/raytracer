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

    // std::ranges::for_each(_objects | std::views::transform([](const auto& obj){ return obj;}));

    for (const auto& obj : _objects)
    {
        
    }

    const auto& obj = _objects[0];
    for(rtsize i = 0; i < _image.size(); ++i)
    {
        const Ray& ray = rays.at(i);
        auto opt = obj.intersect(ray);
        if (opt.has_value())
        {
            auto intersection = opt.value();
            auto toLight = (_settings.lightPosition - (ray.origin() + ray.direction()*intersection.t)).normalize();
            auto diffuseComponenet = dot(intersection.normal, toLight);
            if (diffuseComponenet < 0) diffuseComponenet = 0;
            _image[i] = obj.material().diffuse*diffuseComponenet + (AMBIENT_COMPONENT*obj.material().ambient);
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

auto Renderer::renderIntersection(rtsize pixelIndex, Ray const& ray,  Intersection const &intersection, Material const& material) -> void
{
    auto toLight = (_settings.lightPosition - (ray.origin() + ray.direction()*intersection.t)).normalize();
    auto diffuseComponenet = dot(intersection.normal, toLight);
    if (diffuseComponenet < 0) diffuseComponenet = 0;
    _image[pixelIndex] = material.diffuse*diffuseComponenet + (AMBIENT_COMPONENT*material.ambient);
}

}