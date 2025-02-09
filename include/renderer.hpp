#pragma once
#include "vertex_array.hpp"
#include "element_buffer.hpp"
#include "shader.hpp"

class Renderer
{
private:
public:
    void draw(const VertexArray &va, const ElementBuffer &ib, const Shader &shader) const;
    void clear() const;
};