#pragma once
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

class VertexArray
{
private:
    unsigned int m_vao_id;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout);
    void bind() const;
    void unbind() const;
};