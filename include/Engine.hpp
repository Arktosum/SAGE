#pragma once
#include "Objects.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}
void printVec4(glm::vec4 &vector)
{
    printf("[ %f , %f , %f , %f ]\n", vector[0], vector[1], vector[2], vector[3]);
}
class Engine
{
public:
    Quad *quad;
    Shader *shader;
    Engine()
    {
        shader = new Shader("./shaders/main.vs", "./shaders/main.fs");
        glm::vec2 tl = {0, 0};
        quad = new Quad(shader, tl, 800, 600);
    }
    void render(GLFWwindow *window)
    {
        processInput(window);
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float aspectRatio = (float)width / (float)height;
        double passed_time = glfwGetTime();
        glm::vec2 viewport = {width, height};
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glm::vec2 mousePos = {mouseX, mouseY};

        glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
        shader->setMat4("u_proj", proj);
        shader->setVec2("u_viewport", viewport);
        shader->setVec2("u_mousePos", mousePos);
        quad->draw();
    }
    ~Engine()
    {
    }
};
