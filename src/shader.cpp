#include "../include/shader.h"
#include <iostream>

int Shader::getUniformLocation(const std::string &name)
{
    int location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location == -1)
    {
        std::cerr << "Shader::getUniformLocation failed -1" << std::endl;
        exit(-1);
    }

    return location;
}

void Shader::setUniformMatrix4fv(const std::string &name, glm::mat4 &matrix)
{
    int location = Shader::getUniformLocation(name);
    // GLint location, GLsizei count, GLboolean transpose, const GLfloat *value
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniform1f(const std::string &name, float value)
{
    int location = Shader::getUniformLocation(name);
    glUniform1f(location, value);
}

std::string readFile(const std::string &filename)
{
    std::ifstream file(filename); // Open the file
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(-1);
    }

    std::string content;
    std::string line;
    while (std::getline(file, line))
    {                           // Read line by line
        content += line + "\n"; // Append the line to the content string
    }
    file.close(); // Close the file
    return content;
}

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{

    std::string vertexSrc = readFile(vertexShaderPath);
    std::string fragmentSrc = readFile(fragmentShaderPath);

    const char *vertexSource = vertexSrc.c_str();
    const char *fragmentSource = fragmentSrc.c_str();
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void Shader::use()
{
    glUseProgram(shaderProgram);
}

Shader::~Shader() {
    glDeleteShader(shaderProgram);
}
