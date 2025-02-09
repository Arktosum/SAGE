#include "element_buffer.hpp"
#include "GLManager.hpp"

ElementBuffer::ElementBuffer(const void *buffer_data, unsigned int size)
{
    // we generate a "1" general "buffer" with its id stored in : m_ebo_id
    GLCall(glGenBuffers(1, &m_ebo_id));
    // GL_ELEMENT_ARRAY_BUFFER is the "type" of the EBO structure.
    // We can only bind/select one buffer of a particular type at a time. multiple of different types at a time is okay.
    // Once selected , any buffer calls will reference that buffer.
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id));
    /*
        We send our vertex data to this particular buffer.
        1 - Type of buffer (EBO in this case)
        2 - Total size of vertices. (3 vertices with 3 Dimensions each, 9 floats total, each float is 4 bytes so 36 bytes is the total size.)
        3 - The array reference to copy from the cpu.
        4 - Specifices how GPU should manage the data.
            - GL_STATIC_DRAW: the data is sent only once and used many times. (fastest)
            - GL_STREAM_DRAW: the data is sent only once and used by the GPU at most a few times.(faster)
            - GL_DYNAMIC_DRAW: the data is changed a lot and used many times. (slow)
    */
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer_data, GL_STATIC_DRAW));
}
ElementBuffer::~ElementBuffer()
{
    GLCall(glDeleteBuffers(1, &m_ebo_id));
}

void ElementBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id));
}
void ElementBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}