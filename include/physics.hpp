
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
    void draw(float window_width, float window_height)
    {
        if (position.y < initial_position.y)
        {
            // Done
            return;
        }
        circle->draw(window_width, window_height);
    }
};