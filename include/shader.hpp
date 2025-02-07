#pragma once

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

std::string read_file(const std::string &filepath);

class Shader
{
public:
    unsigned int shaderProgram;
    Shader(const std::string &vertexSourcePath, const std::string &fragmentSourcePath);
    ~Shader();
    void use();
};