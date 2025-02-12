#pragma once

class ElementBuffer
{
private:
    unsigned int m_ebo_id;

public:
    ElementBuffer();
    ~ElementBuffer();

    void loadData(const void *buffer_data, unsigned int size_bytes);
    void bind() const;
    void unbind() const;
};