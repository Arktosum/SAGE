#include <string>
#include <fstream>
#include "glad/glad.h"
#include "../include/glm/glm.hpp"

std::string readFile(const std::string &filename);
class Shader
{
public:
    unsigned int shaderProgram;
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    void use();
    int getUniformLocation(const std::string &name);
    void setUniform1f(const std::string &name, float value);
    void setUniformMatrix4fv(const std::string &name, glm::mat4 &matrix);
    ~Shader();
};