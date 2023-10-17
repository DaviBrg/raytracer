#include "image.h"
#include "ray.h"

namespace
{

auto WriteColor(std::ostream& os, rtracer::color3 const& color) -> void
{
    os << static_cast<int>(255.99 * color.x) << ' ';
    os << static_cast<int>(255.99 * color.y) << ' ';
    os << static_cast<int>(255.99 * color.z) << '\n';
}

}

namespace rtracer
{

Image::Image(rtsize width, rtsize height):
    _width{width}, _height{height}
{
    _buffer.reserve(width*height);
    for (rtsize i=0; i<size(); i++)
    {
        _buffer.emplace_back(0,0,0);
    }
}

auto serializePPM(std::ostream& os, Image const& image) -> void
{
    os << "P3\n" << image.width() << ' '
       << image.height() << '\n' << IMAGE_DEPTH << '\n';

    for (auto const& color : image )
    {
        WriteColor(os, color);
    }
}

}
