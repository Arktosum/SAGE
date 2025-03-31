#pragma once
#include <glad/glad.h>

class VertexBufferObject
{
private:
    unsigned int m_id;

public:
    VertexBufferObject()
    {

        generate_vertex_buffers(1, &m_id); // Only one VAO
    }
    void create_data_store(size_t buffer_size, void *data, unsigned int usage = GL_STATIC_DRAW)
    {
        /*

        target
        Specifies the target buffer object. The symbolic constant must be GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER.

        size
        Specifies the size in bytes of the buffer object's new data store.

        data
        Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.

        usage
        Specifies the expected usage pattern of the data store. The symbolic constant must be GL_STREAM_DRAW, GL_STATIC_DRAW, or GL_DYNAMIC_DRAW.

        */
        bind(); // make sure to bind THIS VBO
        glBufferData(GL_ARRAY_BUFFER, buffer_size, data, usage);
    }
    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }
    static void unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    static void generate_vertex_buffers(unsigned int num_buffers, unsigned int *arrays)
    {
        glGenBuffers(num_buffers, arrays);
    }
    ~VertexBufferObject()
    {
        glDeleteVertexArrays(1, &m_id); // Only one VAO
    }
};