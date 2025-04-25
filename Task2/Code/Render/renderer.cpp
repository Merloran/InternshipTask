#include "renderer.hpp"
#include <cassert>
#include <iostream>
#include <ostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height)
{
    Renderer *renderer = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
    if (renderer)
    {
        renderer->handle_resize(width, height);
    }
}

static void APIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                           GLsizei length, const GLchar *message, const void *userParam)
{
    if (id == 131185 || id == 131218)
    {
        return;
    }
    std::cerr << "OpenGL LOG: " << message << "\n";
}

void Renderer::initialize(const int windowWidth, const int windowHeight, const std::string& windowTitle)
{
    width  = windowWidth;
    height = windowHeight;
    title  = windowTitle;

    init_glfw();
    create_window();

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    init_glad();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl_error_callback, nullptr);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::init_glfw()
{
    if(bool(glfwInit()) == false)
    {
        std::cerr << "Failed to initialize GLFW!\n";
        assert(false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void Renderer::create_window()
{
    assert(window == nullptr && "Windows is already created!");
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
}

void Renderer::init_glad()
{

    if (bool(gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) == false)
    {
        std::cerr << "Failed to initialize OpenGL loader!\n";
        assert(false);
    }
}

void Renderer::create_shader()
{
    assert(shader == 0 && "Shader is already created!");
    // I write glsl code here, because I think it is no need for loading shader from file
    constexpr std::string_view VERT_CODE = "#version 330 core									  \n"
                                           "layout(location = 0) in vec2 position;				  \n"
                                           "													  \n"
                                           "uniform vec2 offset;								  \n"
                                           "													  \n"
                                           "void main()										      \n"
                                           "{													  \n"
                                           "    gl_Position = vec4(position + offset, 0.0f, 1.0f);\n"
                                           "}													  \n";

    constexpr std::string_view FRAG_CODE = "#version 330 core				                      \n"
                                           "out vec4 outColor;				                      \n"
                                           "								                      \n"
                                           "uniform vec3 color;				                      \n"
                                           "								                      \n"
                                           "void main()						                      \n"
                                           "{								                      \n"
                                           "    outColor = vec4(color, 1.0f);                     \n" 
                                           "}	                                                  \n";

    const uint32_t vertModule = glCreateShader(GL_VERTEX_SHADER);
    const char *vertCodeSource = VERT_CODE.data();
    glShaderSource(vertModule, 1, &vertCodeSource, nullptr);
    glCompileShader(vertModule);

    const uint32_t fragModule = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragCodeSource = FRAG_CODE.data();
    glShaderSource(fragModule, 1, &fragCodeSource, nullptr);
    glCompileShader(fragModule);

    shader = glCreateProgram();
    glAttachShader(shader, vertModule);
    glAttachShader(shader, fragModule);

    glLinkProgram(shader);

    glDeleteShader(vertModule);
    glDeleteShader(fragModule);
}

void Renderer::use_shader()
{
    assert(shader != 0 && "Shader is not created!");
    glUseProgram(shader);
}

bool Renderer::should_close() const
{
    return bool(glfwWindowShouldClose(window)) == true;
}

void Renderer::poll_events()
{
    glfwPollEvents();
}

void Renderer::clear_color()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swap_buffers()
{
    glfwSwapBuffers(window);
}

GLFWwindow *Renderer::get_window() const
{
    return window;
}

uint32_t Renderer::get_shader() const
{
    return shader;
}

float Renderer::get_delta_time()
{
    const float currentFrame = float(glfwGetTime());
    const float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltaTime;
}

void Renderer::handle_resize(const int newWidth, const int newHeight)
{
    width = newWidth;
    height = newHeight;

    glViewport(0, 0, width, height);
}

void Renderer::cleanup()
{
    if (shader != 0)
    {
        glDeleteProgram(shader);
        shader = 0;
    }

    if (window != nullptr)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}
