#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

class Window
{
public:
    GLFWwindow *window;
    unsigned int width, height;
    std::string window_name;
    Window(unsigned int width, unsigned int height, std::string window_name);
    void setup(void (*callback)());
    void loop(void (*callback)());
    ~Window();
};