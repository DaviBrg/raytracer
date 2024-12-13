#pragma once

#include <vector>

#include "camera.h"
#include "image.h"
#include "object.h"

namespace rtracer
{

struct Renderer
{

    struct Settings
    {
        point3 eye;
        point3 at;
        rtfloat focalDistance;
        rtfloat viewportHeight;
        point3 lightPosition;
        color3 backgroundColor;
    };

    Renderer(Image& image, vec3 eye, vec3 at, rtfloat focalDistance, rtfloat viewportHeight, point3 lightPosition);

    Renderer(Image& image, Settings settings);

    auto render() const -> void;

    auto updateRenderingSettings(Settings settings) -> void;

    auto addObject(Object object) -> void;

private:
    Image& _image;
    Settings _settings;
    Camera _camera;
    std::vector<Object> _objects;

    using ObjectIntersection = std::pair<Object const*,std::optional<Intersection>>;

    auto renderIntersection(rtsize pixelIndex, Ray const& ray, Intersection const& intersection, Material const& material) const -> void;
    auto closestIntersection(Ray const& ray) const -> ObjectIntersection;
    auto canReachLightSource(point3 intersection) const -> bool;

};


}