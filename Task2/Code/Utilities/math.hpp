#pragma once
#include <array>

struct Vec2;
struct Bounds;
struct Triangle;

namespace Math
{
    Vec2 perpendicular(Vec2 vector);

    float dot(Vec2 vector1,Vec2 vector2);

    Bounds project_triangle(const Triangle &triangle, Vec2 axis);

    std::array<Vec2, 6> get_axes(const Triangle &t1, const Triangle &t2);

    bool is_collide(const Triangle &triangle1, const Triangle &triangle2);

}
