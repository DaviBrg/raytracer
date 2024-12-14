#include <catch2/catch_all.hpp>

#include <algorithm>

#include "camera.h"

namespace rtracer
{

TEST_CASE("General camera tests", "[camera]")
{
    auto expectedRays = PixelRays{};
    expectedRays.reserve(4);

    auto origin = vec3{0.0, 0.0, -1.0};
    expectedRays.emplace_back(0, Ray{origin, vec3{-0.5, 0.5, 1.0}});
    expectedRays.emplace_back(1, Ray{origin, vec3{0.5, 0.5, 1.0}});
    expectedRays.emplace_back(2, Ray{origin, vec3{-0.5, -0.5, 1.0}});
    expectedRays.emplace_back(3, Ray{origin, vec3{0.5, -0.5, 1.0}});

    auto settings = Camera::Settings{};

    auto camera = Camera{settings};
    auto generatedRays = camera.createRays();

    REQUIRE(generatedRays.size() == expectedRays.size());
    auto areRaysEqual = std::equal(std::begin(expectedRays), std::end(expectedRays), std::begin(generatedRays),
    [](PixelRay const& lhs, PixelRay const& rhs)
    {
        return (lhs.ray.origin() == rhs.ray.origin()) && (lhs.ray.direction() == rhs.ray.direction());
    });

    REQUIRE(areRaysEqual);

}

}
