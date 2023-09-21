#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>

#include "./lib/window.h"
#include <vector>

class Shader
{
    unsigned int shaderProgram;

public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
    {
        // Load and compile shaders
        std::string vertexShaderString = readFile(vertexShaderPath);
        std::string fragmentShaderString = readFile(fragmentShaderPath);

        const char *vertexShaderSource = vertexShaderString.c_str();
        const char *fragmentShaderSource = fragmentShaderString.c_str();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Create a shader program and link the shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    std::string readFile(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cerr << "Could not open file: " << filepath << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    void useProgram()
    {
        glUseProgram(shaderProgram);
    }
    ~Shader()
    {
        glDeleteProgram(shaderProgram);
    }
};

class Renderer
{
    protected:
    unsigned int VAO, VBO;
    std::vector<float> vertices;

public:
    Renderer()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void updateVBO()
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~Renderer()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

class PointRenderer : public Renderer{
    public:
    PointRenderer(){}
    void addPoint(float x, float y, float z)
    {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        updateVBO();
    }
    void render()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
        glBindVertexArray(0);
    }
};

class RectRenderer : public Renderer{
    public:
    void setRect(float x, float y, float width, float height){
        vertices.clear();
        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;

        // Rectangle vertices
        float rectVertices[] = {
            x - halfWidth, y - halfHeight,0.0f,
            x + halfWidth, y - halfHeight,0.0f,
            x + halfWidth, y + halfHeight,0.0f,
            x - halfWidth, y + halfHeight,0.0f
        };
        vertices.insert(vertices.end(), rectVertices, rectVertices + 12);
        updateVBO();
    }
    void draw(GLenum mode = GL_LINE_LOOP) {
        glBindVertexArray(VAO);
        glDrawArrays(mode, 0, vertices.size() / 3);
        glBindVertexArray(0);
    }
};

void doEvery(double& x, double& y,double fps = 60.0){
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    double interval = 1/fps;
    if (currentTime - lastTime >=interval)
    {
        // Do here 
        RectRenderer rect;
        rect.setRect(x,y,0.5f,0.2f);
        rect.draw();

        x+=0.0001f;
        y-=0.0001f;

        lastTime = currentTime;
    }
}




int main()
{
    Window window(800, 800, "Hello OpenGL!");

    
    Shader shader("./shaders/vert.glsl", "./shaders/frag.glsl");
    double x = 0.0f;
    double y= 0.0f;
    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
      
        shader.useProgram();
        doEvery(x,y);
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}

