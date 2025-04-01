#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>

std::string readFile(const std::string &filepath)
{
    // std::filesystem::path currentPath = std::filesystem::current_path();
    // std::cout << "Current working directory: " << currentPath << std::endl;

    std::ifstream fileStream(filepath);
    if (!fileStream.is_open())
    {
        std::cerr << "Error: Could not open shader file " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();

    return buffer.str();
}

class Shader
{
private:
    unsigned int shader_program;

public:
    Shader() {}
    Shader(std::string vertex_shader_path, std::string fragment_shader_path)
    {
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, readFile(vertex_shader_path));
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, readFile(fragment_shader_path));
        linkShaders(vertexShader, fragmentShader);
    }
    unsigned int compileShader(int shaderType, std::string source_code)
    {
        bool is_vertex_shader = shaderType == GL_VERTEX_SHADER;
        // ShaderType =
        const char *source = source_code.c_str();
        // vertex shader
        unsigned int shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::" << (is_vertex_shader ? "VERTEX" : "FRAGMENT") << "::SHADER::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
        return shader;
    }
    void use()
    {
        glUseProgram(shader_program);
    }
    void linkShaders(unsigned int vertexShader, unsigned int fragmentShader)
    {
        // link shaders
        shader_program = glCreateProgram();
        glAttachShader(shader_program, vertexShader);
        glAttachShader(shader_program, fragmentShader);
        glLinkProgram(shader_program);

        // check for linking errors

        int success;
        char infoLog[512];

        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    ~Shader()
    {
        glDeleteProgram(shader_program);
    }
    int getUniformLocation(const std::string &name) const
    {
        int location = glGetUniformLocation(shader_program, name.c_str());
        if (location == -1)
        {
            printf("Cannot find uniform name: %s", name);
            exit(-1);
        }
        return location;
    }
    void setBool(const std::string &name, bool value) const
    {

        glUniform1i(getUniformLocation(name), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
    }
    void setMat4(const std::string &name, glm::mat4 &matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void setVec3(const std::string &name, glm::vec3 &vector) const
    {
        glUniform3f(glGetUniformLocation(shader_program, name.c_str()), vector[0], vector[1], vector[2]);
    }
    void setVec2(const std::string &name, glm::vec2 &vector) const
    {
        glUniform2f(glGetUniformLocation(shader_program, name.c_str()), vector[0], vector[1]);
    }
};
