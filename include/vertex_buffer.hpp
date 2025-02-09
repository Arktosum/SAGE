#pragma once

class VertexBuffer
{
private:
    unsigned int m_vbo_id;

public:
    VertexBuffer(const void *buffer_data, unsigned int size);
    ~VertexBuffer();

    void bind() const; 
    void unbind() const;
};