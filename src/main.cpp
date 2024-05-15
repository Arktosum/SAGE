#include <iostream>
#include <string>
#include "../include/window.h"
#include "../include/shader.h"
#include "../include/VBO.h"
#include "../include/IBO.h"
#include "math.h"
#include "../include/glm/glm.hpp"

Window window(1920, 1080, "Hello OpenGL!");
Shader shader("../shaders/vert.glsl", "../shaders/frag.glsl");

double previousTime = 0;
unsigned int VBO, VAO, EBO;

void setup()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        1.0f, 1.0f, 0.0f,   // top right
        1.0f, -1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, // bottom left
        -1.0f, 1.0f, 0.0f   // top left
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
    int location = glGetUniformLocation(shader.shaderProgram, "u_time");
    glUniform1f(location, time);

    shader.use();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main()
{
    // window.setup(setup);
    // window.loop(loop);
    return 0;
}
