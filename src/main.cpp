#include "image.h"
#include <fstream>

auto main() -> int
{
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
