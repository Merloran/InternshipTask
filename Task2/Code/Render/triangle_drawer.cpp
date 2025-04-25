#include "triangle_drawer.hpp"

#include <cassert>
#include <glad/glad.h>

void TriangleDrawer::initialize(const Triangle &triangle)
{
    assert(vao == 0 || vbo == 0 && "TriangleDrawer is already initialized!");
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), &triangle, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriangleDrawer::draw(const uint32_t shader) const
{
    assert(vao != 0 && "TriangleDrawer is not initialized!");
    glUniform2f(glGetUniformLocation(shader, "offset"), offset.x, offset.y);
    glUniform3f(glGetUniformLocation(shader, "color"), color.r, color.g, color.b);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleDrawer::cleanup()
{
    assert(vao != 0 && vbo != 0 && "GL objects were already freed");
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
    vbo = 0;
}