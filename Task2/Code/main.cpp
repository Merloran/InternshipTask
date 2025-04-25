#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Render/renderer.hpp"
#include "Render/triangle_drawer.hpp"
#include "Utilities/math.hpp"

int main()
{
    Renderer renderer{};
    renderer.initialize(1024, 768, "Triangle Collision");

    Triangle triangle1 =
    {
        Vec2{  0.3f,  0.5f },
        Vec2{  0.0f,  1.0f },
        Vec2{ -0.5f,  1.0f }
    };
    TriangleDrawer triangle1Drawer;
    triangle1Drawer.initialize(triangle1);
    triangle1Drawer.color = { 0.0f, 1.0f, 0.0f };
    triangle1Drawer.velocity = 0.3f;

    Triangle triangle2 =
    {
        Vec2{  0.3f,  0.0f },
        Vec2{  0.0f,  0.5f },
        Vec2{ -0.5f,  0.0f }
    };
    TriangleDrawer triangle2Drawer;
    triangle2Drawer.initialize(triangle2);
    triangle2Drawer.color = { 1.0f, 0.0f, 0.0f };

    renderer.create_shader();
    renderer.use_shader();

    while (renderer.should_close() == false)
    {
        float deltaTime = renderer.get_delta_time();
        renderer.clear_color();
        glfwPollEvents();

        if (glfwGetKey(renderer.get_window(), GLFW_KEY_W) == GLFW_PRESS)
        {
            triangle1Drawer.offset.y += triangle1Drawer.velocity * deltaTime;
        }
        if (glfwGetKey(renderer.get_window(), GLFW_KEY_S) == GLFW_PRESS)
        {
            triangle1Drawer.offset.y -= triangle1Drawer.velocity * deltaTime;
        }
        if (glfwGetKey(renderer.get_window(), GLFW_KEY_D) == GLFW_PRESS)
        {
            triangle1Drawer.offset.x += triangle1Drawer.velocity * deltaTime;
        }
        if (glfwGetKey(renderer.get_window(), GLFW_KEY_A) == GLFW_PRESS)
        {
            triangle1Drawer.offset.x -= triangle1Drawer.velocity * deltaTime;
        }

        if (Math::is_collide(triangle1 + triangle1Drawer.offset, triangle2))
        {
            triangle1Drawer.color = { 1.0f, 0.0f, 0.0f };
            triangle2Drawer.color = { 1.0f, 0.0f, 0.0f };
        } else {
            triangle1Drawer.color = { 0.0f, 1.0f, 0.0f };
            triangle2Drawer.color = { 0.0f, 1.0f, 0.0f };
        }

        triangle1Drawer.draw(renderer.get_shader());
        triangle2Drawer.draw(renderer.get_shader());

        renderer.swap_buffers();
    }

    triangle1Drawer.cleanup();
    triangle2Drawer.cleanup();
    renderer.cleanup();

    return 0;
}