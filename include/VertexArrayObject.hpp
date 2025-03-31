#pragma once
#include <glad/glad.h>

class VertexArrayObject
{
private:
    unsigned int m_id;
    unsigned int location_index = 0;
    uintptr_t offset = 0;

public:
    VertexArrayObject()
    {
        glGenVertexArrays(1, &m_id); // Only one VAO
    }
    void bind()
    {
        glBindVertexArray(m_id);
    }
    static void unbind()
    {
        glBindVertexArray(0);
    }

    ~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &m_id); // Only one VAO
    }

    void setAttribute(
        unsigned int components_in_attribute = 3, // only 1,2,3,4
        GLenum data_type = GL_FLOAT,
        unsigned int should_normalize = GL_FALSE, // true or false
        unsigned int stride = 0                   // how many bytes in one Vertex (one Vertex has multiple attributes)
    )

    {
        if (location_index == 16)
        {
            printf("Error: Maximum limit of attributes in a VAO is only 16!");
            exit(-1);
        }
        // [V1,V2,V3.....Vn]
        // [{A1,A2},{A1,A2}....]
        // stride: number of bytes between v1 and v2 aka size of each Vertex
        // offset : size of bytes from 0 to that particular attribute , i.e , for An the offsetis size(A0 + A1 +....An-1)
        /*

        index
        Specifies the index of the generic vertex attribute to be modified.

        size
        Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant GL_BGRA is accepted by glVertexAttribPointer. The initial value is 4.

        type
        Specifies the data type of each component in the array. The symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT are accepted by glVertexAttribPointer and glVertexAttribIPointer. Additionally GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV and GL_UNSIGNED_INT_10F_11F_11F_REV are accepted by glVertexAttribPointer. GL_DOUBLE is also accepted by glVertexAttribLPointer and is the only token accepted by the type parameter for that function. The initial value is GL_FLOAT.

        normalized
        For glVertexAttribPointer, specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.

        stride
        Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.

        pointer
        Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.

        */

        bind(); // Bind this VAO
        glVertexAttribPointer(location_index, components_in_attribute, data_type, should_normalize, stride, (void *)offset);
        // enable for this attribute in this location
        glEnableVertexAttribArray(location_index);
        location_index++;

        offset += components_in_attribute * getDataTypeSize(data_type);
    }
    size_t getDataTypeSize(GLenum data_type)
    {
        switch (data_type)
        {
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_INT:
            return sizeof(GLint);
        // Add cases for other data types as needed
        default:
            printf("Unknown data type, size cannot be determined!");
            exit(-1);
        }
    }
};
