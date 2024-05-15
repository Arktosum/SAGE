#include <string>
#include <fstream>
#include "glad/glad.h"

std::string readFile(const std::string &filename);
class Shader
{
public:
    unsigned int shaderProgram;
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    void use();
    ~Shader();
};