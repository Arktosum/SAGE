
#include <iostream>
#include <VertexArrayObject.hpp>
#include <VertexBufferObject.hpp>
#include <ElementBufferObject.hpp>
#include <Shader.hpp>
#include <Window.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window = Window(SCR_WIDTH, SCR_HEIGHT, "Open GL");
    Engine engine = Engine();
    window.render(engine);
    return 0;
}
