#include <fstream>
#include <chrono>

#include "renderer.h"
#include "image.h"
#include "object.h"
#include "sphere.h"
#include "vec3.h"


auto main() -> int
{
    rtracer::Image img{2*1920,2*1080};

    auto rendererSettings = rtracer::Renderer::Settings{};
    rendererSettings.eye = rtracer::point3{25, 25, 35};
    rendererSettings.at = rtracer::point3{0.0, 0.0, 0.0};
    rendererSettings.focalDistance = 1.0;
    rendererSettings.viewportHeight = 1.0;
    rendererSettings.lightPosition = rtracer::point3{30.0, 15.0, 0.0};
    rendererSettings.backgroundColor = rtracer::rgbColor(173, 216, 230);

    auto renderer = rtracer::Renderer(img, rendererSettings);

// rtracer::rgbColor(140, 115, 12)
// rtracer::rgbColor(255, 215, 0)

    auto goldenMaterial = rtracer::Material{rtracer::rgbColor(255, 215, 0), rtracer::rgbColor(255, 215, 0), rtracer::rgbColor(255, 255, 255)};
    auto greenMaterial = rtracer::Material{rtracer::rgbColor(20, 90, 50), rtracer::rgbColor(39, 174, 96), rtracer::rgbColor(255, 255, 255)};

    constexpr rtracer::rtfloat floorRadius = 1000000.0;
    constexpr rtracer::rtfloat sphere1Radius = 3.0;
    constexpr rtracer::rtfloat sphere2Radius = 5.0;
    constexpr rtracer::rtfloat sphere3Radius = 8.0;
    renderer.addObject(rtracer::Object{rtracer::Sphere{rtracer::point3{0.0, -floorRadius, 0.0}, floorRadius, greenMaterial}});
    renderer.addObject(rtracer::Object{rtracer::Sphere{rtracer::point3{0.0, sphere1Radius, 0.0}, sphere1Radius, goldenMaterial}});
    renderer.addObject(rtracer::Object{rtracer::Sphere{rtracer::point3{-8.0, sphere2Radius, -8.0}, sphere2Radius, goldenMaterial}});
    renderer.addObject(rtracer::Object{rtracer::Sphere{rtracer::point3{-20.0, sphere3Radius, -20.0}, sphere3Radius, goldenMaterial}});


    auto before = std::chrono::steady_clock::now();
    renderer.render();
    auto after = std::chrono::steady_clock::now();

    std::cout << "\nRendering duration: " << std::chrono::duration_cast<std::chrono::seconds>(after - before).count() << " seconds \n";

    std::ofstream file{"test.ppm"};

    rtracer::serializePPM(file, img);

    file.flush();


    return 0;
}
