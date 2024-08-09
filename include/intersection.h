#pragma once

#include "vec3.h"
#include "rtincludes.h"

namespace rtracer
{

struct Intersection
{
    rtfloat t = {};
    vec3 normal = {};
};

}