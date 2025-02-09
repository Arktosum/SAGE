#pragma once

#include <glad/glad.h>

class VAO
{
public:
    unsigned int vao;
    VAO();
    ~VAO();
    void bind();
    void setVertexAttributePointer(unsigned int vertex_attribute_layout, unsigned int dimension_of_vertex, unsigned int vertex_data_type, unsigned int should_normalize, unsigned int stride_or_vertex_size);
};