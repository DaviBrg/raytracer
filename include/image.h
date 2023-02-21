#pragma once

#include <vector>

#include "rtincludes.h"
#include "vec3.h"

namespace rtracer
{

constexpr rtsize const IMAGE_DEPTH = 255;

struct Image
{
    explicit Image(rtsize width, rtsize height);

    auto width() const -> rtsize
    {
        return _width;
    }

    auto height() const -> rtsize
    {
        return _height;
    }

    auto size() const -> rtsize
    {
        return _width * _height;
    }

    auto begin() const
    {
        return _buffer.begin();
    }

    auto end() const
    {
        return _buffer.end();
    }

    auto cbegin() const -> auto
    {
        return _buffer.cbegin();
    }

    auto cend() const -> auto
    {
        return _buffer.cend();
    }

    auto operator[](size_t index) -> auto&
    {
        return _buffer.at(index);
    }

    auto operator[](size_t index) const -> auto const&
    {
        return _buffer.at(index);
    }

private:
    rtsize _width, _height;
    std::vector<color3> _buffer;
};

void serializePPM(std::ostream& os, Image const& image);

}
