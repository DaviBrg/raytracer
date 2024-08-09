#include <fstream>

#include "renderer.h"
#include "image.h"
#include "object.h"
#include "sphere.h"
#include "vec3.h"


auto main() -> int
{
    rtracer::Image img{1000,1000};

    auto rendererSettings = rtracer::Renderer::Settings{};
    rendererSettings.eye = rtracer::point3{30.0, 30.0, 30.0};
    rendererSettings.at = rtracer::point3{0.0, 0.0, 0.0};
    rendererSettings.focalDistance = 1.0;
    rendererSettings.viewportHeight = 1.0;
    rendererSettings.lightPosition = rtracer::point3{0.0, 10.0, 0.0};
    rendererSettings.backgroundColor = rtracer::rgbColor(173, 216, 230);

    auto renderer = rtracer::Renderer(img, rendererSettings);

// rtracer::rgbColor(140, 115, 12)
// rtracer::rgbColor(255, 215, 0)

    auto goldenMaterial = rtracer::Material{rtracer::rgbColor(255, 215, 0), rtracer::rgbColor(255, 215, 0), rtracer::rgbColor(255, 255, 255)};
    renderer.addObject(rtracer::Object{rtracer::Sphere{rtracer::point3{0.0, 0.0, 0.0}, 3.0, goldenMaterial}});

    renderer.render();

    std::ofstream file{"test.ppm"};

    rtracer::serializePPM(file, img);

    file.flush();


    return 0;
}
