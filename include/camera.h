#pragma once

#include "rtincludes.h"
#include "ray.h"
#include "vec3.h"

namespace rtracer
{

struct PixelRay
{
    rtsize pixel;
    Ray ray;
};

using PixelRays = std::vector<PixelRay>;

struct Camera
{
    struct Settings
    {
        rtfloat viewportHeight{2.0};
        rtsize pixelsHeight{2};
        rtfloat viewportRatio{1.0};
        rtfloat focalLength{1.0};
        point3 eye{0.0, 0.0, -1.0};
        point3 at{0.0, 0.0, 0.0};
        vec3 up{0.0, 1.0, 0.0};
    };

    explicit Camera(Settings const&);


    [[nodiscard]] auto viewportHeight() const noexcept -> rtfloat
    {
        return _viewportHeight;
    }

    [[nodiscard]] auto viewportRatio() const noexcept -> rtfloat
    {
        return _viewportRatio;
    }

    [[nodiscard]] auto viewportWidth() const noexcept -> rtfloat
    {
        return _viewportWidth;
    }

    [[nodiscard]] auto pixelsHeight() const noexcept -> rtsize
    {
        return _pixelsHeight;
    }

    [[nodiscard]] auto pixelsWidth() const noexcept -> rtsize
    {
        return _pixelsWidth;
    }

    [[nodiscard]] auto focalLength() const noexcept -> rtfloat
    {
        return _focalLength;
    }

    [[nodiscard]] auto createRays() const -> PixelRays;


    private:
    rtfloat _viewportHeight;
    rtfloat _viewportRatio;
    rtfloat _viewportWidth;
    rtsize _pixelsHeight;
    rtsize _pixelsWidth;
    rtfloat _focalLength;
    vec3 _up;
    vec3 _lookAt;
    vec3 _u;
    vec3 _v;
    point3 _eye;
    point3 _at;
};


}