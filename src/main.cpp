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

void update(float deltaTime)
{
    ball->rk4Update(deltaTime);
}
void render()
{
    float window_width = window->screen_width;
    float window_height = window->screen_height;
    ball->draw(window_width, window_height);
}

const float fps = 144;
const float second_per_frame = 1.0f / fps;
float accumulator = 0;

int frames = 0;
float fpsTimer = 0.0f;

int main()
{
    printf("Time step : %f", second_per_frame);
    window = new Window(1920, 1080);
    float window_width = window->screen_width;
    float window_height = window->screen_height;
    ball = new Ball(glm::vec2(200.0f, window_height / 4));
    ball->startParameters(3.1415926 / 4, 120.0f);
    float previousTime = glfwGetTime();
    while (!window->shouldClose())
    {
        window->processInput(window->getWindow());

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        accumulator += deltaTime;

        // 🔁 Run physics updates at fixed steps
        while (accumulator >= second_per_frame)69
        {
            update(second_per_frame);
            accumulator -= second_per_frame;
        }
        // 🎨 Render once per frame
        window->clear(0, 0, 0, 1);

        render();
        window->swapBuffers();
        window->pollEvents();
    }

    return 0;
}
