#pragma once

class VertexBuffer
{
public:
    unsigned int vbo_id;
    VertexBuffer(const void *data, unsigned int size);
    void bind();
    void unbind();
    ~VertexBuffer();
};