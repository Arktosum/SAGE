#include "window.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
    {
        // Wireframe Mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        // Normal mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

Window::Window(unsigned int width = 800, unsigned int height = 600, const char *title = "Test window") : width(width), height(height), title(title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (this->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    // Behind the scenes OpenGL uses the data specified via glViewport to transform the 2D coordinates it processed to coordinates on your screen.
    // For example, a processed point of location (-0.5,0.5) would (as its final transformation) be mapped to (200,450) in screen coordinates.
    // Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
}

void Window::run(void (*render)())
{

    while (!glfwWindowShouldClose(this->window))
    {
        /*
            ----------------
            Double buffer
            ----------------
            When an application draws in a single buffer the resulting image may display flickering issues.
            This is because the resulting output image is not drawn in an instant, but drawn pixel by pixel and usually from left to right and top to bottom.
            Because this image is not displayed at an instant to the user while still being rendered to, the result may contain artifacts.
            To circumvent these issues, windowing applications apply a double buffer for rendering.
            The front buffer contains the final output image that is shown at the screen, while all the rendering commands draw to the back buffer.
            As soon as all the rendering commands are finished we swap the back buffer to the front buffer so the image can be displayed without still being rendered to, removing all the aforementioned artifacts.
        */
        // input
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(this->window);
        // rendering commands here
        render();
        // check and call events and swap the buffers
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}
Window::~Window()
{
    // Clean up GLFW resources.
    glfwTerminate();
}