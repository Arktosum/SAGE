
#include <iostream>
#include <glad/glad.h>
#include "window.hpp"
#include "shader.hpp"
#include "object.hpp"
#include <math.h>


int main()
{
    Window window(1920, 1080);
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");
    Rectangle rect;

    glm::mat4 trans = glm::mat4(1.0f);
   

    while (!window.shouldClose())
    {
        window.processInput(window.getWindow()); // or inline in class
        window.clear(0, 0, 0, 1);
        float currentTime = glfwGetTime();
        trans = glm::rotate(trans, (float)(2*M_PI*(1+glm::sin(0.01*currentTime))/2), glm::vec3(0.0f, 0.0f, 1.0f));

        shader.setFloat("u_time", currentTime);
        shader.setMat4("u_MVP",trans);

        // draw our first triangle
        shader.use();
        rect.draw();

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}
