#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{

public:
    Window(const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);
    ~Window();
    bool shouldClose() const { return glfwWindowShouldClose(window); }
    void swapBuffers() const { glfwSwapBuffers(window); }
    void pollEvents() const { glfwPollEvents(); }
    void clear(float r = 0, float g = 0, float b = 0, float a = 1) const
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    GLFWwindow *getWindow() const { return window; }
    static void processInput(GLFWwindow *w);
    void setTitle(const std::string title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }

    unsigned int screen_width;
    unsigned int screen_height;

private:
    GLFWwindow *window = NULL;

    // internal callbacks
    static void framebuffer_size_callback(GLFWwindow *w, int width, int height);
};