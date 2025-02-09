#include "vertex_array.hpp"
#include <iostream>
#include <cstdint>

#include "GLManager.hpp"

VertexArray::VertexArray()
{
    // Bind VAO first. then bind VBOs and attrib pointers to this VAO.

    GLCall(glGenVertexArrays(1, &m_vao_id));
}
VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_vao_id));
}

void VertexArray::addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout)
{
    bind();
    vbo.bind();
    const std::vector<VertexBufferAttribute> &attributes = layout.getAttributes();
    uintptr_t offset = 0;
    const unsigned int stride = layout.getStride();
    for (int attribute_index = 0; attribute_index < attributes.size(); attribute_index++)
    {
        const VertexBufferAttribute &attribute = attributes[attribute_index];
        GLCall(glVertexAttribPointer(attribute_index, attribute.dimension, attribute.datatype, attribute.should_normalize, stride, (const void *)offset));
        GLCall(glEnableVertexAttribArray(attribute_index));
        offset += attribute.dimension * attribute.datatype_size;
    }
}
void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_vao_id));
}
void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}