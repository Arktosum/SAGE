#include <iostream>
#include <string>
#include "../include/window.h"
#include "../include/shader.h"
#include "../include/VBO.h"
#include "../include/IBO.h"
#include "math.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

Window window(1920, 1080, "Hello OpenGL!");
Shader shader("../shaders/vert.glsl", "../shaders/frag.glsl");

double previousTime = 0;
unsigned int VBO, VAO, EBO;

void setup()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    // VAO
    // VBO
    // ATTRIB
    // EBO

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    VertexBuffer vbo(vertices, sizeof(vertices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    IndexBuffer ibo(indices, 6);
    glBindVertexArray(0);
}

void loop()
{

    double time = glfwGetTime();
    float angle = glm::radians(100 * time);
    glm::vec3 axis(0.0f, 0.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 rotationMatrix = glm::rotate(model, angle, axis);
    model = rotationMatrix * model;
    shader.setUniform1f("u_time", time);
    shader.setUniformMatrix4fv("u_matrix", model);
    shader.use();
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
int main()
{
    window.setup(setup);
    window.loop(loop);
    return 0;
}
