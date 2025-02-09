#include "GLManager.hpp"
#include <GLFW/glfw3.h>
#include "renderer.hpp"
#include "texture.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Open GL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    // Behind the scenes OpenGL uses the data specified via glViewport to transform the 2D coordinates it processed to coordinates on your screen.
    // For example, a processed point of location (-0.5,0.5) would (as its final transformation) be mapped to (200,450) in screen coordinates.
    // Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).
    glViewport(0, 0, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader("./shaders/vert.glsl", "./shaders/frag.glsl");
    // --------------------------------------------------------------------------------------------------

    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);

    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout rectangle_layout;
    rectangle_layout.pushAttribute(3, GL_FLOAT, false);
    rectangle_layout.pushAttribute(2, GL_FLOAT, false);
    vao.addBuffer(vbo, rectangle_layout);
    ElementBuffer ebo(indices, sizeof(indices));

    shader.bind();

    Texture texture("./assets/duck.jpg");
    unsigned int texture_slot = 0;
    texture.bind(texture_slot);
    shader.setUniform1i("u_texture", texture_slot);

    shader.unbind();
    ebo.unbind();
    vbo.unbind();
    vao.unbind();

    Renderer renderer;
    while (!glfwWindowShouldClose(window))
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
        processInput(window);
        // ------------------- rendering commands here ------------------
        renderer.clear();
        // send uniforms here
        renderer.draw(vao, ebo, shader);
        // ---------------------------------------------------------------------
        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

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
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }
    else
    {
        // Normal mode
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    }
}