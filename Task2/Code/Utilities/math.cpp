#include "math.hpp"
#include "structures.hpp" 
#include <limits>
#include <cmath>

Vec2 Math::perpendicular(Vec2 vector)
{
    return { -vector.y, vector.x };
}

float Math::dot(Vec2 vector1, Vec2 vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

Bounds Math::project_triangle(const Triangle &triangle, Vec2 axis)
{
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();
    for (Vec2 point : triangle.points)
    {
        float projection = dot(axis, point);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
    return { min, max };
}

std::array<Vec2, 6> Math::get_axes(const Triangle &t1, const Triangle &t2)
{
    std::array<Vec2, 6> axes;
    for (size_t i = 0; i < 3; ++i)
    {
        Vec2 edge = t1.points[(i + 1) % 3] - t1.points[i];
        Vec2 axis = perpendicular(edge);
        float length = std::sqrt(dot(axis, axis));
        if (length > 0)
        {
            axis = { axis.x / length, axis.y / length };
        }
        axes[i] = axis;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        Vec2 edge = t2.points[(i + 1) % 3] - t2.points[i];
        Vec2 axis = perpendicular(edge);
        float length = std::sqrt(dot(axis, axis));
        if (length > 0)
        {
            axis = { axis.x / length, axis.y / length };
        }
        axes[i + 3] = axis;
    }
    return axes;
}

bool Math::is_collide(const Triangle &triangle1, const Triangle &triangle2)
{
    std::array<Vec2, 6> axes = get_axes(triangle1, triangle2);
    for (const Vec2 axis : axes)
    {
        auto [min1, max1] = project_triangle(triangle1, axis);
        auto [min2, max2] = project_triangle(triangle2, axis);
        const bool isNotOverlap = max1 < min2 || max2 < min1;
        if (isNotOverlap)
        {
            return false;
        }
    }
    return true;
}