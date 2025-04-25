#pragma once
#include <array>

struct Vec2
{
    float x, y;

    Vec2 operator-(const Vec2 other) const noexcept
    {
        return { x - other.x, y - other.y };
    }

    Vec2 operator+(const Vec2 other) const noexcept
    {
        return { x + other.x, y + other.y };
    }

};

struct Triangle
{
    std::array<Vec2, 3> points;

    Triangle operator+(const Vec2 vector) const noexcept
    {
        Triangle result{};
        result.points[0] = points[0] + vector;
        result.points[1] = points[1] + vector;
        result.points[2] = points[2] + vector;

        return result;
    }
};

struct Color
{
    float r, g, b;
};

struct Bounds
{
    float min, max;
};