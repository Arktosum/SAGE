#include "VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &this->vao);
}
void VAO::setVertexAttributePointer(unsigned int vertex_attribute_layout, unsigned int dimension_of_vertex, unsigned int vertex_data_type, unsigned int should_normalize, unsigned int stride_or_vertex_size, const void *offset)
{
    glVertexAttribPointer(vertex_attribute_layout, dimension_of_vertex, vertex_data_type, should_normalize, stride_or_vertex_size, offset);
    glEnableVertexAttribArray(vertex_attribute_layout);
}
VAO::~VAO()
{
}

void VAO::bind()
{
    // Bind VAO first. then bind VBOs and attrib pointers to this VAO.
    // only need to bind the VAO to get same results.
    glBindVertexArray(this->vao);
}

void VAO::unbind()
{
    // unbinds VAO
    glBindVertexArray(0);
}
