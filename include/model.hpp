// Interface (Abstract Class)
// class Model
// {
// public:
//     virtual void draw() = 0; // Pure virtual function (must be overridden)
//     virtual ~Drawable() {}   // Virtual destructor
// };

// Class implementing the interface
// class Circle : public Model
// {
// public:
//     void draw() override
//     {
//         cout << "Drawing a Circle" << endl;
//     }
// };

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vertex_buffer.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"
#include "element_buffer.hpp"

#include <iostream>
#include <math.h>

class Cube
{

private:
    VertexArray m_vao;
    VertexBuffer m_vbo, m_instance_vbo;
    Shader m_shader;
    unsigned int m_instanceCount;

public:
    Cube(unsigned int instanceCount, const std::string &vertexSourcePath, const std::string &fragmentSourcePath)
        : m_vao(), m_vbo(), m_instance_vbo(), m_shader(vertexSourcePath, fragmentSourcePath), m_instanceCount(instanceCount)
    {
        // Vertex Attrib Pointer = 3*float (vertex position)
        float cube_vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f};
        VertexBufferLayout cube_layout;
        m_vbo.loadData(cube_vertices, sizeof(cube_vertices));
        cube_layout.pushAttribute(3, GL_FLOAT, false);
        m_vao.addBuffer(m_vbo, cube_layout);

        m_vao.bind();
        // **Create instance buffer for model matrices**
        std::vector<glm::mat4> modelMatrices(m_instanceCount);
        int index = 0;
        for (int x = 0; x < 100; x++)
        {
            for (int z = 0; z < 100; z++)
            {
                modelMatrices[index] = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z));
                index++;
            }
        }

        // **Bind instance buffer**
        m_instance_vbo.bind();
        m_instance_vbo.loadData(modelMatrices.data(), m_instanceCount * sizeof(glm::mat4));

        // **Setup attribute pointers for instance data (model matrix)**
        for (int i = 0; i < 4; i++) // Mat4 takes 4 attribute slots
        {
            glEnableVertexAttribArray(1 + i);
            glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                                  (void *)(sizeof(glm::vec4) * i)); // Offset per column
            glVertexAttribDivisor(1 + i, 1);                        // Per-instance data
        }
        // **Unbind everything to prevent accidental modifications**
        m_instance_vbo.unbind();
        m_vbo.unbind();
        m_vao.unbind();
    };
    void set_mvp(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection)
    {
        m_shader.bind();
        m_shader.setUniformMat4fv("u_model", model);
        m_shader.setUniformMat4fv("u_view", view);
        m_shader.setUniformMat4fv("u_projection", projection);
    }

    void set_vp(glm::mat4 &view, glm::mat4 &projection)
    {
        m_shader.bind();
        m_shader.setUniformMat4fv("u_view", view);
        m_shader.setUniformMat4fv("u_projection", projection);
    }
    void display()
    {
        m_shader.bind();
        m_vao.bind();
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, m_instanceCount);
    }
};

class Axes
{

private:
    VertexArray m_vao;
    VertexBuffer m_vbo;
    ElementBuffer m_ebo;
    Shader m_shader;

public:
    Axes(const std::string &vertexSourcePath, const std::string &fragmentSourcePath) : m_vao(), m_vbo(), m_ebo(), m_shader(vertexSourcePath, fragmentSourcePath)
    {
        // Vertex Attrib Pointer = 3*float (vertex position)
        float axes_vertices[] = {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f};

        unsigned int axes_indices[] = {
            0, 1,
            0, 2,
            0, 3};
        VertexBufferLayout axes_layout;
        m_vbo.loadData(axes_vertices, sizeof(axes_vertices));
        axes_layout.pushAttribute(3, GL_FLOAT, false);
        m_vao.addBuffer(m_vbo, axes_layout);
        m_ebo.loadData(axes_indices, sizeof(axes_indices));
    };
    void set_mvp(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection)
    {
        m_shader.bind();
        m_shader.setUniformMat4fv("u_model", model);
        m_shader.setUniformMat4fv("u_view", view);
        m_shader.setUniformMat4fv("u_projection", projection);
    }
    void display()
    {
        m_shader.bind();
        m_vao.bind();
        m_ebo.bind();
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
    }
};

struct vec3
{
    float x, y, z;
};

void push_vec3(std::vector<float> &vertices, vec3 vertex)
{
    vertices.push_back(vertex.x);
    vertices.push_back(vertex.y);
    vertices.push_back(vertex.z);
}

class Circle
{

private:
    VertexArray m_vao;
    VertexBuffer m_vbo;
    // ElementBuffer m_ebo;
    Shader m_shader;
    unsigned int m_vertexCount;

public:
    Circle(const std::string &vertexSourcePath, const std::string &fragmentSourcePath) : m_vao(), m_vbo(), m_shader(vertexSourcePath, fragmentSourcePath)
    {
        
    };
    void set_mvp(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection)
    {
        m_shader.bind();
        m_shader.setUniformMat4fv("u_model", model);
        m_shader.setUniformMat4fv("u_view", view);
        m_shader.setUniformMat4fv("u_projection", projection);
    }
    void display()
    {
        m_shader.bind();
        m_vao.bind();
        glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexCount);
    }
};

/*

glDrawArrays — render primitives from array data

Parameters
GLenum mode
Specifies what kind of primitives to render. Symbolic constants
GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.

GLint first
Specifies the starting index in the enabled arrays. (usually zero )

GLsizei count
Specifies the number of vertices to be rendered.

*/

/*

Name
glDrawElements — render primitives from array data
Parameters
GLenum mode
Specifies what kind of primitives to render. Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.

GLsizei count
Specifies the number of elements to be rendered. a.k.a count of the indices array.

GLenum type
Specifies the type of the values in indices. Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.

const void *  indices
Specifies a pointer to the location where the indices are stored.

*/
