#pragma once
#include <cstdint>
#include <string>

struct GLFWwindow;

class Renderer
{
private:
    GLFWwindow *window = nullptr;
    uint32_t shader = 0;
    int width = 0;
    int height = 0;
    std::string title{};
    float lastFrame = 0.0f;

public:
    void initialize(int32_t windowWidth = 1024,
                    int32_t windowHeight = 768,
                    const std::string &windowTitle = "Triangle Collision");

    bool should_close() const;
    void poll_events();
    void clear_color();
    void create_shader();
    void use_shader();
    void swap_buffers();
    GLFWwindow *get_window() const;
    uint32_t get_shader() const;
    float get_delta_time();
    void handle_resize(int newWidth, int newHeight);

    void cleanup();

private:
    void init_glfw();
    void create_window();
    void init_glad();
};
