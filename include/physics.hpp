
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "object.hpp"

void printVec2(const std::string parameter, glm::vec2 vector)
{
    printf("%s : [ %f , %f ]\n", parameter.c_str(), vector.x, vector.y);
}
class Ball
{
public:
    glm::vec2 position;
    glm::vec2 velocity = {0, 0};
    glm::vec2 acceleration = {0, -10};
    glm::vec2 initial_position;
    float h_max = 0;
    float start_y;
    float range = 0;
    Circle *circle;
    Ball(glm::vec2 position) : position(position)
    {
        initial_position = {position.x, position.y};
        circle = new Circle(position, 20.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
    void startParameters(float angle_radians, float start_velocity)
    {
        velocity = {start_velocity * glm::cos(angle_radians),
                    start_velocity * glm::sin(angle_radians)};
    }
    void update(float deltaTime)
    {
        if (position.y < initial_position.y)
        {
            // Done
            return;
        }
        // Euler's method
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        circle->position = position;
        h_max = glm::max(position.y, h_max);

        range = glm::max(position.x, range);
        printVec2("XY", glm::vec2(range, h_max) - initial_position);
    }
    void rk4Update(float dt)
    {
        if (position.y < initial_position.y)
            return;

        glm::vec2 k1_v = acceleration;
        glm::vec2 k1_p = velocity;

        glm::vec2 k2_v = acceleration;
        glm::vec2 k2_p = velocity + 0.5f * dt * k1_v;

        glm::vec2 k3_v = acceleration;
        glm::vec2 k3_p = velocity + 0.5f * dt * k2_v;

        glm::vec2 k4_v = acceleration;
        glm::vec2 k4_p = velocity + dt * k3_v;

        velocity += dt / 6.0f * (k1_v + 2.0f * k2_v + 2.0f * k3_v + k4_v);
        position += dt / 6.0f * (k1_p + 2.0f * k2_p + 2.0f * k3_p + k4_p);

        h_max = glm::max(position.y, h_max);
        range = glm::max(position.x, range);
        printVec2("XY", glm::vec2(range, h_max) - initial_position);
    }
    void draw(float window_width, float window_height)
    {
        if (position.y < initial_position.y)
        {
            // Done
            return;
        }
        circle->position = position;
        circle->draw(window_width, window_height);
    }
};
