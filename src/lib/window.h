#include "../../include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "../../include/GLFW/glfw3.h"

#include <iostream>

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

        // Configure GLFW to use modern OpenGL (version 3.3, core profile)
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

        // Set the current OpenGL context to this window
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
        // Terminate GLFW when the window is closed
        glfwTerminate();
    }

    bool shouldClose() const
    {
        // Check if the window should close
        return glfwWindowShouldClose(window);
    }

    void swapBuffers()
    {
        // Swap the front and back buffers to display rendered content
        glfwSwapBuffers(window);
    }

    void pollEvents()
    {
        // Poll for and process events
        glfwPollEvents();
    }

    GLFWwindow *getGLFWWindow() const
    {
        // Get the GLFW window
        return window;
    }

private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // Adjust the viewport when the window is resized
        glViewport(0, 0, width, height);
    }
};