#include "renderer.hpp"
#include "GLManager.hpp"

void Renderer::draw(const VertexArray &vao, const ElementBuffer &ibo, const Shader &shader) const
{
    shader.bind();
    vao.bind();
    ibo.bind();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void Renderer::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}