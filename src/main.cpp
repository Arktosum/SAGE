
#include <iostream>
#include <glad/glad.h>
#include "window.hpp"
#include "shader.hpp"
#include "object.hpp"
#include <math.h>
#include "physics.hpp"
Window *window;
Shader *shader;
Ball *ball;
void render(float deltaTime)
{
    float window_width = window->screen_width;
    float window_height = window->screen_height;
    ball->draw(window_width, window_height);
    ball->update(deltaTime);
}

const float fps = 60;
const float second_per_frame = 1.0f / fps;
unsigned int frames = 0;
int main()
{

    window = new Window(1920, 1080);
    float window_width = window->screen_width;
    float window_height = window->screen_height;
    ball = new Ball(glm::vec2(200.0f, window_height / 4));
    ball->startParameters(3.14159 / 4, 120.0f);
    float previousTime = glfwGetTime();
    while (!window->shouldClose())
    {
        window->processInput(window->getWindow()); // or inline in class

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - previousTime;
        frames++;
        if (deltaTime >= second_per_frame)
        {
            window->setTitle("FPS " + std::to_string(frames));
            window->clear(0, 0, 0, 1);
            render(deltaTime);
            previousTime = currentTime;
            window->swapBuffers();
            frames = 0;
        }

        window->pollEvents();
    }

    return 0;
}
