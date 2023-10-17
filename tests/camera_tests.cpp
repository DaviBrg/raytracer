#include <catch2/catch_all.hpp>

#include <algorithm>

#include "camera.h"

namespace rtracer
{

TEST_CASE("General camera tests", "[camera]")
{
    auto expectedRays = Rays{};
    expectedRays.reserve(4);

    auto origin = vec3{0.0, 0.0, -1.0};
    expectedRays.emplace_back(origin, vec3{-0.5, 0.5, 1.0});
    expectedRays.emplace_back(origin, vec3{0.5, 0.5, 1.0});
    expectedRays.emplace_back(origin, vec3{-0.5, -0.5, 1.0});
    expectedRays.emplace_back(origin, vec3{0.5, -0.5, 1.0});

    auto settings = Camera::Settings{};

    auto camera = Camera{settings};
    auto generatedRays = camera.CreateRays();

    REQUIRE(generatedRays.size() == expectedRays.size());
    auto areRaysEqual = std::equal(std::begin(expectedRays), std::end(expectedRays), std::begin(generatedRays),
    [](Ray const& lhs, Ray const& rhs)
    {
        return (lhs.Origin() == rhs.Origin()) && (lhs.Direction() == rhs.Direction());
    });

    REQUIRE(areRaysEqual);

}

}
