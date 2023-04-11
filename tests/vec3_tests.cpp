#include <catch2/catch_all.hpp>

#include "vec3.h"

namespace rtracer
{

TEST_CASE("vec3 operations", "[vec3]")
{
    vec3 v = {1,2,3};

    REQUIRE(v == v);
    REQUIRE((v + v) == 2*v);
    REQUIRE((v + v) == v*2);
    REQUIRE(v == (2*v - v));
    REQUIRE(v*v == vec3{1,4,9});
    REQUIRE(v/2 == v*0.5);
    REQUIRE(v.normalize().length() == 1.0);
    REQUIRE(cross(vec3{1.0,0.0,0.0}, vec3{0.0,1.0,0.0}) == vec3{0.0,0.0,1.0});
    REQUIRE(cross(vec3{0.0,1.0,0.0}, vec3{0.0,0.0,1.0}) == vec3{1.0,0.0,0.0});
    REQUIRE(dot(vec3{2.0,2.0,2.0}, vec3{3.0,3.0,3.0}) == 18.0);
}

}
