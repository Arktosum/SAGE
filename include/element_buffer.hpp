#pragma once

class ElementBuffer
{
private:
    unsigned int m_ebo_id;

public:
    ElementBuffer(const void *buffer_data, unsigned int size);
    ~ElementBuffer();

    void bind() const;
    void unbind() const;
};