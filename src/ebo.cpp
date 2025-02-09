#include "EBO.hpp"

EBO::EBO()
{
    glGenBuffers(1, &this->ebo);
}

EBO::~EBO()
{
}

void EBO::bind()
{
    // GL_ARRAY_BUFFER is the "type" of the VBO structure.
    // We can only bind/select one buffer of a particular type at a time. multiple of different types at a time is okay.
    // Once selected , any buffer calls will reference that buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}
void EBO::setBufferData(unsigned int *indices, size_t buffer_size, GLenum usage)
{
    /*
         We send our vertex data to this particular buffer.
         1 - Type of buffer (VBO in this case)
         2 - Total size of vertices. (3 vertices with 3 Dimensions each, 9 floats total, each float is 4 bytes so 36 bytes is the total size.)
         3 - The array reference to copy from the cpu.
         4 - Specifices how GPU should manage the data.
             - GL_STATIC_DRAW: the data is sent only once and used many times. (fastest)
             - GL_STREAM_DRAW: the data is sent only once and used by the GPU at most a few times.(faster)
             - GL_DYNAMIC_DRAW: the data is changed a lot and used many times. (slow)
     */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, indices, usage);
}
