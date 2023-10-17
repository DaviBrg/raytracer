#include "camera.h"

#include <cmath>

namespace rtracer
{

Camera::Camera(Settings const& settings):
    _viewportHeight{settings.viewportHeight},
    _viewportRatio{settings.viewportRatio},
    _viewportWidth{_viewportHeight * _viewportRatio},
    _pixelsHeight{settings.pixelsHeight},
    _pixelsWidth{static_cast<rtsize>(round((_viewportWidth*_pixelsHeight)/_viewportHeight))},
    _focalLength{settings.focalLength},
    _up{settings.up.normalize()},
    _lookAt{(settings.at - settings.eye).normalize()},
    _u{-cross(_lookAt, _up)},
    _v{cross(_u, _lookAt)},
    _eye{settings.eye},
    _at{settings.at} {}

auto Camera::CreateRays() const -> Rays
{
    Rays result;
    rtfloat heightStep = _viewportHeight/_pixelsHeight;
    rtfloat widthStep = _viewportWidth/_pixelsWidth;
    auto topLeft = _eye + ((_at - _eye).normalize()*_focalLength) + ((-_u)*(_viewportWidth*0.5)) + ((-_v)*(_viewportHeight*0.5));

    point3 start = topLeft + _u*heightStep*0.5 + _v*widthStep*0.5;

    for (rtsize height = 0; height < _pixelsHeight; ++height)
    {
        for (rtsize width = 0; width < _pixelsWidth; ++width)
        {
            vec3 at = start + (_u*widthStep*width) + (_v*heightStep*height);
            result.emplace_back(_eye, at - _eye);
        }
    }
    return result;
}

}

