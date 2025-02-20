#include "GLManager.hpp"
#include <GLFW/glfw3.h>
#include "texture.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "camera.hpp"
#include "model.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 1920.0f / 2.0f;
float lastY = 1080.0f / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f; // Time between current frame and last frame
GLFWwindow *window;

void glfw_init_window(unsigned int width, unsigned int height, const std::string &title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

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
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE); // Enables us to change the point size in the shader.
}
int main()
{
    glfw_init_window(1920, 1080, "SAGE");
    // --------------------------------------------------------------------------------------------------
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
    // --------------------------------------------------------------------------------------------------

    // Cube cube(100 * 100, "./shaders/cube/cube.vert", "./shaders/cube/cube.frag");
    Axes axes("./shaders/axes/axes.vert", "./shaders/axes/axes.frag");
    Circle circle("./shaders/circle/circle.vert", "./shaders/circle/circle.frag");

    float lastFrame = 0.0f; // Time of last frame
    float fov = 45.0f;
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
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui::ShowDemoWindow(); // Show demo window! :)
        // input
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        int window_width, window_height;
        glfwGetWindowSize(window, &window_width, &window_height);
        float aspect_ratio = (float)window_width / (float)window_height;
        std::cout << "window_width: " << window_width << " window_height: " << window_height << std::endl;
        processInput(window);
        {

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            // ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            // ImGui::Checkbox("Another Window", &show_another_window);
            // ImGui::SliderFloat("Light Position X", &lightPos.x, -5.0f, 5.0f);
            // ImGui::SliderFloat("Light Position Y", &lightPos.y, -5.0f, 5.0f);
            // ImGui::SliderFloat("Light Position Z", &lightPos.z, -5.0f, 5.0f);

            // ImGui::ColorEdit3("Object color", &objectColor.x); // Edit 3 floats representing a color
            // ImGui::ColorEdit3("light color", &lightColor.x);   // Edit 3 floats representing a color

            // ImGui::SliderFloat("u_ambientStrength", &u_ambientStrength, 0.1f, 1.0f);
            ImGui::SliderFloat("zoom", &camera.Zoom, -180.0f, 180.0f);
            // ImGui::SliderFloat("u_specularStrength", &u_specularStrength, 0.1f, 1.0f);

            // if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
            //     counter++;
            // ImGui::SameLine();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            // ImGui::Text("cameraPos : %.3f %.3f %.3f", camera.Position.x, camera.Position.y, camera.Position.z);

            ImGui::End();
        }
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        // ------------------- rendering commands here ------------------

        // ---------------------------------------------------------------------
        // {
        //     glm::mat4 model(1.0f);
        //     glm::mat4 view = camera.GetViewMatrix();
        //     glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspect_ratio, 0.1f, 100.0f);
        //     axes.set_mvp(model, view, projection);
        //     axes.display();
        // }
        // --------------------------------------------------------------------
        // glm::mat4 view = camera.GetViewMatrix();
        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)1920 / (float)1080, 0.1f, 100.0f);
        // cube.set_vp(view, projection);
        // cube.display();
        // ---------------------------------------------------------------------

        // ---------------------------------------------------------------------
        {
            glm::mat4 model(1.0f);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 200.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
            circle.set_mvp(model, view, projection);
            circle.display();
        }
        // --------------------------------------------------------------------
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // check and call events and swap the buffers
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    exit(0);
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
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.disableMouse = false;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        camera.disableMouse = true;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}