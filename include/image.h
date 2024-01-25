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

    [[nodiscard]] auto width() const noexcept -> rtsize
    {
        return _width;
    }

    [[nodiscard]] auto height() const noexcept -> rtsize
    {
        return _height;
    }

    [[nodiscard]] auto size() const noexcept -> rtsize
    {
        return _width * _height;
    }

    [[nodiscard]] auto begin() const noexcept -> auto
    {
        return _buffer.begin();
    }

    [[nodiscard]] auto end() const noexcept -> auto
    {
        return _buffer.end();
    }

    [[nodiscard]] auto cbegin() const noexcept -> auto
    {
        return _buffer.cbegin();
    }

    [[nodiscard]] auto cend() const noexcept -> auto
    {
        return _buffer.cend();
    }

    [[nodiscard]] auto operator[](size_t index) noexcept -> color3&
    {
        return _buffer.at(index);
    }

    [[nodiscard]] auto operator[](size_t index) const noexcept -> color3 const&
    {
        return _buffer.at(index);
    }

private:
    rtsize _width, _height;
    std::vector<color3> _buffer;
};

void serializePPM(std::ostream& os, Image const& image);

}
