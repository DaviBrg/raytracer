#include "image.h"

namespace
{

void write_color(std::ostream& os, rtracer::color3 const& color)
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

void serializePPM(std::ostream &os, Image const& image)
{
    os << "P3\n" << image.width() << ' '
       << image.height() << '\n' << IMAGE_DEPTH << '\n';

    for (auto const& color : image )
    {
        write_color(os, color);
    }
}

}
