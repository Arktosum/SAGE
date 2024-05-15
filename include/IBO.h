#pragma once

class IndexBuffer
{
public:
    unsigned int ibo_id;
    unsigned int count;
    IndexBuffer(const unsigned int *data, unsigned int count);
    void bind();
    void unbind();
    ~IndexBuffer();
};