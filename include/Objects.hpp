#pragma once
#include "Shader.hpp"
#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Quad
{
private:
    VertexArrayObject m_vao;
    VertexBufferObject m_vbo;
    ElementBufferObject m_ebo;
    Shader *m_shader;

public:
    Quad() {};
    Quad(Shader *shader, glm::vec2 &tl, float width, float height) : m_shader(shader)
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        // float vertices[] = {
        //     0.5f, 0.5f, 0.0f,   // top right
        //     0.5f, -0.5f, 0.0f,  // bottom right
        //     -0.5f, -0.5f, 0.0f, // bottom left
        //     -0.5f, 0.5f, 0.0f   // top left
        // };

        glm::vec2 tr = {tl.x + width, tl.y};
        glm::vec2 bl = {tl.x, tl.y + height};
        glm::vec2 br = {bl.x + width, bl.y};
        float vertices[] = {
            tr.x, tr.y, 0.0f, // top right
            br.x, br.y, 0.0f, // bottom right
            bl.x, bl.y, 0.0f, // bottom left
            tl.x, tl.y, 0.0f  // top left
        };

        unsigned int indices[] = {
            // note that we start from 0!
            0, 1, 3, // first Triangle
            1, 2, 3  // second Triangle
        };

        m_vao.bind();

        m_vbo.create_data_store(sizeof(vertices), vertices, GL_STATIC_DRAW);
        m_ebo.create_data_store(sizeof(indices), indices, GL_STATIC_DRAW);

        m_vao.setAttribute(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

        VertexBufferObject::unbind();
        VertexArrayObject::unbind();
    }
    void draw()
    {
        m_vao.bind();
        m_shader->use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};

/*
glDrawArrays
    mode
    Specifies what kind of primitives to render. Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.

    first
    Specifies the starting index in the enabled arrays.

    count
    Specifies the number of indices to be rendered.
*/

/*
GlDrawElements
mode
Specifies what kind of primitives to render. Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.

count
Specifies the number of elements to be rendered.

type
Specifies the type of the values in indices. Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.

indices
Specifies a pointer to the location where the indices are stored.

*/

/*

POINT PRIMITIVE:
GL_POINTS

LINE PRIMITIVES:

GL_LINES: Vertices 0 and 1 are considered a line. Vertices 2 and 3 are considered a line. And so on. If the user specifies a non-even number of vertices, then the extra vertex is ignored.
GL_LINE_STRIP: The adjacent vertices are considered lines. Thus, if you pass n vertices, you will get n-1 lines. If the user only specifies 1 vertex, the drawing command is ignored.
GL_LINE_LOOP: As line strips, except that the first and last vertices are also used as a line. Thus, you get n lines for n input vertices. If the user only specifies 1 vertex, the drawing command is ignored. The line between the first and last vertices happens after all of the previous lines in the sequence.


TRIANGLE PRIMITIVES:abs
GL_TRIANGLES: Vertices 0, 1, and 2 form a triangle. Vertices 3, 4, and 5 form a triangle. And so on.
GL_TRIANGLE_STRIP: Every group of 3 adjacent vertices forms a triangle. The face direction of the strip is determined by the winding of the first triangle. Each successive triangle will have its effective face order reversed, so the system compensates for that by testing it in the opposite way. A vertex stream of n length will generate n-2 triangles.
GL_TRIANGLE_FAN: The first vertex is always held fixed. From there on, every group of 2 adjacent vertices form a triangle with the first. So with a vertex stream, you get a list of triangles like so: (0, 1, 2) (0, 2, 3), (0, 3, 4), etc. A vertex stream of n length will generate n-2 triangles.
*/

