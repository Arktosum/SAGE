#include "shader.hpp"

std::string read_file(const std::string &filepath)
{
    // std::cout << "Current Path: " << std::filesystem::current_path() << std::endl;
    std::string result = "";
    std::string line = "";
    std::ifstream file(filepath.c_str());
    // Reading file line by line is the way to go. otherwise receive shader problems during compilation
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            result += line + "\n"; // This new line is also required!
        }
        file.close();
    }
    return result;
}

Shader::Shader(const std::string &vertexSourcePath, const std::string &fragmentSourcePath)
{
    // Read in shader file
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    // 1 - ID of shader
    // 2 - Total number of strings ( only one in this case which is the whole program)
    // 3 - The source file string
    // 4 - NULL
    const char *vertex_shader = read_file(vertexSourcePath).c_str();

    glShaderSource(vertexShaderID, 1, &vertex_shader, NULL);
    glCompileShader(vertexShaderID);
    // Check if shader compilation is a success..
    {
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
            exit(-1);
        }
    }

    // ----------------------------------------------------------------------
    const char *fragment_shader = read_file(fragmentSourcePath).c_str();
    // const char *fragment_shader = "#version 330 core\n"
    //                               "out vec4 FragColor;\n"
    //                               "void main()\n"
    //                               "{\n"
    //                               "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //                               "}";
    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    // 1 - ID of shader
    // 2 - Total number of strings ( only one in this case which is the whole program)
    // 3 - The source file string
    // 4 - NULL
    glShaderSource(fragmentShaderID, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShaderID);
    // Check if shader compilation is a success..
    {
        int success;
        char infoLog[512];
        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
            exit(-1);
        }
    }

    // a Shader program contains multiple combined shaders.
    // We can select one shader program that will be used when we issue render calls.

    this->shaderProgram = glCreateProgram();

    glAttachShader(this->shaderProgram, vertexShaderID);
    glAttachShader(this->shaderProgram, fragmentShaderID);
    glLinkProgram(this->shaderProgram);
    // Check if shader program linking is a success..
    {
        int success;
        char infoLog[512];
        glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
            exit(-1);
        }
    }
    // Delete shaders once we link them
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

Shader::~Shader()
{
}

void Shader::use()
{
    glUseProgram(this->shaderProgram);
}