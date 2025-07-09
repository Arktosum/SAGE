#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

private:
    GLFWwindow *window = NULL;
    unsigned int m_screen_width;
    unsigned int m_screen_height;

    // internal callbacks
    static void framebuffer_size_callback(GLFWwindow *w, int width, int height);
};