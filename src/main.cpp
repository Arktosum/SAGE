#include <iostream>
#include "window.hpp"
#include "shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include <math.h>

unsigned int shaderProgram;
unsigned int vao_id;

void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    // Send uniforms
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // Draw stuff.
    glBindVertexArray(vao_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

int main()
{
    Window window(1920, 1080, "SAGE - Engine");

    Shader shader("./shaders/vert.glsl", "./shaders/frag.glsl");
    shaderProgram = shader.shaderProgram;

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // Bind VAO first. then bind VBOs and attrib pointers to this VAO.
    // only need to bind the VAO to get same results.
    VAO vao;
    VBO vbo;
    EBO ebo;
    vao_id = vao.vao;
    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    ebo.bind();
    ebo.setBufferData(indices, sizeof(indices), GL_STATIC_DRAW);
    vao.setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

    window.run(render);
    return 0;
}

/*
Bind VAO
BindBuffer / select buffer  VBO
send BufferData vertex_data

set Vertex attrib pointer
set enable attrib array

render loop :
    use shader program
    bind VAO
    use function to draw using given vertices.
*/