#pragma once
#include <glad/glad.h>

class Rectangle
{
private:
    GLuint VAO, VBO;

public:
    Rectangle(float width_px, float height_px)
    {
        float vertices[] = {
            0.0f, 0.0f, 0.0f,
            width_px, 0.0f, 0.0f,
            width_px, height_px, 0.0f,
            0.0f, height_px, 0.0f};

        GLuint indices[] = {
            0, 1, 2,
            2, 3, 0};

        GLuint EBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }
    ~Rectangle()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
    void draw() const
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

class Circle
{
public:
    Rectangle *rect;
    glm::vec2 position;
    float radius;
    glm::vec3 color;
    Shader *shader;
    Circle(glm::vec2 position, float radius, glm::vec3 color) : position(position), radius(radius), color(color)
    {
        rect = new Rectangle(2 * radius, 2 * radius);
        shader = new Shader("./shaders/circle_shader.vert", "./shaders/circle_shader.frag");
    }
    void draw(float window_width, float window_height)
    {

        shader->use();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0)); // position in pixels
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::ortho(0.0f, float(window_width), 0.0f, float(window_height)); // pixels as coordinates

        glm::mat4 mvp = proj * view * model;
        shader->setMat4("u_mvp", mvp);
        shader->setFloat("u_radius", radius);
        shader->setVec2("u_center", glm::vec2(radius, radius));
        shader->setVec3("u_color", color);

        rect->draw();
    }
};

class Line
{
private:
    GLuint VAO, VBO;

public:
    Line(float x1, float y1, float x2, float y2)
    {
        float vertices[] = {
            x1, y1, 0.0f,
            x2, y2, 0.0f};

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }
    ~Line()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
    void draw() const
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    }
    void update(float x1, float y1, float x2, float y2)
    {
        float vertices[] = {
            x1, y1, 0.0f,
            x2, y2, 0.0f
        };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    }
};
