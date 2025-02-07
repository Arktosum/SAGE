#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
class Window
{
public:
    GLFWwindow *window;
    unsigned int width, height;
    const char *title;
    Window(unsigned int width, unsigned int height, const char *title);
    void run(void (*render)());
    ~Window();
};