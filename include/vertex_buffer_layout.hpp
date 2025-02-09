#pragma once
#include <glad/glad.h>
#include <vector>
#include <iostream>
struct VertexBufferAttribute
{
    unsigned int dimension;     // What dimension does this attribute have?
    GLenum datatype;            // what is the datatype of this attribute.
    bool should_normalize;      // should this attribute be normalized? i.e scaled between -1 and 1?
    unsigned int datatype_size; // what is the size of the datatype of this attribute
};

class VertexBufferLayout
{
    // Contains multiple attributes like , vertex , color , texture etc..
    // Combination of all attributes forms a "ELEMENT"
    // Stride = sizeof("ELEMENT") = sizeof(attribute1) + sizeof("attribute2") + ...
    // Offset = sizeof(attribute1) + sizeof("attribute2") + ... current attribute ( basically points to the current attribute in every "element" )
    // stride is the total size of ALL attributes combined.
    // offset is the running size taken to point to the start of the current attribute.

private:
    std::vector<VertexBufferAttribute> m_attributes;
    unsigned int m_stride = 0;

public:
    VertexBufferLayout()
    {
    }
    ~VertexBufferLayout()
    {
    }

    void pushAttribute(unsigned int attribute_dimension, GLenum attribute_datatype, bool should_normalize)
    {
        // NOTE : Only attribute_datatype of GL_FLOAT is added so far!, If required , more to be added here.
        unsigned int attribute_datatype_size = 0;
        if (attribute_datatype == GL_FLOAT)
        {
            attribute_datatype_size = sizeof(GLfloat);
        }

        m_attributes.push_back({attribute_dimension, attribute_datatype, should_normalize, attribute_datatype_size});
        m_stride += attribute_dimension * attribute_datatype_size;
    }
    inline const std::vector<VertexBufferAttribute> getAttributes() const { return m_attributes; }
    inline const unsigned int getStride() const { return m_stride; }
};