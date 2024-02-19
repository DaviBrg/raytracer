#include <fstream>

#include "object.h"
#include "image.h"
#include "object.h"


namespace rtracer
{

struct Circle
{
    [[nodiscard]] auto Intersect(Ray const& ray) const noexcept -> std::optional<Intersection>
    {
        return {};
    }
};

}


auto main() -> int
{
    auto obj = rtracer::Object{rtracer::Circle{}};

    auto obj2 = obj;

    auto intersec = obj2.Intersect(
        rtracer::Ray{
            rtracer::point3{0,0,0},
            rtracer::vec3{0,0,0}
    });

    rtracer::Image img{2,2};

    img[0] = rtracer::color3(1,0,0);
    img[1] = rtracer::color3(0,1,0);
    img[2] = rtracer::color3(0,0,1);
    img[3] = rtracer::color3(1,0,1);

    std::ofstream file{"test.ppm"};

    rtracer::serializePPM(file, img);

    file.flush();
    return 0;
}
