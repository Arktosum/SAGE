#pragma once

#include <glad/glad.h>

class VBO
{
public:
    unsigned int vbo;
    VBO();
    ~VBO();
    void bind();
    void setBufferData(float *vertices, size_t buffer_size, GLenum usage);
};