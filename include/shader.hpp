#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ShaderType
{
    VERTEX_SHADER = 0,
    FRAGMENT_SHADER = 1
};

std::string read_file(const std::string &filepath);

class Shader
{
private:
    unsigned int m_shader_program_id = 0;
    std::unordered_map<std::string, int> m_uniform_location_cache;
    int getUniformLocation(const std::string &uniform_name);

public:
    Shader(const std::string &vertexSourcePath, const std::string &fragmentSourcePath);
    ~Shader();
    unsigned int createShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);
    unsigned int compileShader(ShaderType type, const std::string &file_path);
    void bind() const;
    void unbind() const;
    void setUniform4f(const std::string &uniform_name, glm::vec4 &vector);
    void setUniform3f(const std::string &uniform_name, glm::vec3 &vector);

    void setUniform1i(const std::string &uniform_name, int value);
    void setUniform1f(const std::string &uniform_name, float value);
    void setUniformMat4fv(const std::string &uniform_name, glm::mat4 &matrix);

};