#pragma once

#include <glad/glad.h>

class EBO
{
public:
    unsigned int ebo;
    EBO();
    ~EBO();
    void bind();
    void setBufferData(unsigned int *indices, size_t buffer_size, GLenum usage);
};