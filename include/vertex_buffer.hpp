#pragma once

class VertexBuffer
{
private:
    unsigned int m_vbo_id;

public:
    VertexBuffer();
    ~VertexBuffer();
    void loadData(const void *buffer_data, unsigned int size_bytes);
    void bind() const; 
    void unbind() const;
};