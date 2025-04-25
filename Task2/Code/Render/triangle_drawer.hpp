#pragma once
#include <cstdint>

#include "Utilities/structures.hpp"

struct Triangle;

class TriangleDrawer
{
public:
    Vec2 offset{};
    Color color{};
    float velocity{};

private:
    uint32_t vao{};
    uint32_t vbo{};

public:
    TriangleDrawer() = default;

    void initialize(const Triangle &triangle);

    void draw(uint32_t shader) const;

    void cleanup();
};