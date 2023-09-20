#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>

#include "../include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "../include/GLFW/glfw3.h"

class Window
{
private:
    GLFWwindow *window;
public:
    Window(int width, int height, const std::string &title)
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Configure GLFW to use modern OpenGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            std::exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    ~Window()
    {
        glfwTerminate();
    }
    bool shouldClose() const
    {
        return glfwWindowShouldClose(window);
    }
    void swapBuffers()
    {
        glfwSwapBuffers(window);
    }
    void pollEvents()
    {
        glfwPollEvents();
    }
    GLFWwindow *getGLFWWindow() const
    {
        return window;
    }

private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height){
        glViewport(0, 0, width, height);
    }
};

int main()
{
    Window window(800, 800, "Hello OpenGL");

    while (!window.shouldClose())
    {
        // Input handling
        window.pollEvents();

        window.swapBuffers();
    }

    return 0;
}