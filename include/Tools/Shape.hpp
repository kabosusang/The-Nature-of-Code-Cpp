#pragma once
#include "Color.hpp"
#include "Vector.hpp"

struct Sphere {
	Vec3 center;
	float radius;
	Color color;
    int specular = 0;
    float reflective = 0.0f;
};
