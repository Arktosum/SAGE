#include "vertex_buffer.hpp"
#include "GLManager.hpp"

VertexBuffer::VertexBuffer()
{
    // we generate a general "buffer" with an id of 1.
    GLCall(glGenBuffers(1, &m_vbo_id));
}

void VertexBuffer::loadData(const void *buffer_data, unsigned int size_bytes)
{
    // GL_ARRAY_BUFFER is the "type" of the VBO structure.
    // We can only bind/select one buffer of a particular type at a time. multiple of different types at a time is okay.
    // Once selected , any buffer calls will reference that buffer.
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id));
    /*
    glBufferData — create and initialize a buffer object's data store

    @params
    GLenum target
    Specifies the target buffer object. The symbolic constant must be GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER.

    GLsizeiptr size
    Specifies the size in bytes of the buffer object's new data store.

    const void * data
    Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.

    GLenum usage
    Specifies the expected usage pattern of the data store. The symbolic constant must be GL_STREAM_DRAW, GL_STATIC_DRAW, or GL_DYNAMIC_DRAW.

    */
    GLCall(glBufferData(GL_ARRAY_BUFFER, size_bytes, buffer_data, GL_STATIC_DRAW));

    /*
    STREAM
    The data store contents will be modified once and used at most a few times.

    STATIC
    The data store contents will be modified once and used many times.

    DYNAMIC
    The data store contents will be modified repeatedly and used many times.
    */
}
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_vbo_id));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id));
}
void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}