#include "shader.hpp"
#include "GLManager.hpp"

#include <string>

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

    unsigned int vertex_shader_id = compileShader(ShaderType::VERTEX_SHADER, vertexSourcePath);
    unsigned int fragment_shader_id = compileShader(ShaderType::FRAGMENT_SHADER, fragmentSourcePath);

    m_shader_program_id = createShaderProgram(vertex_shader_id, fragment_shader_id);
}
Shader::~Shader()
{
    GLCall(glDeleteProgram(m_shader_program_id));
}

unsigned int Shader::createShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id)
{
    // a Shader program contains multiple combined shaders.
    // We can select one shader program that will be used when we issue render calls.
    GLCall(unsigned int shader_program_id = glCreateProgram());

    GLCall(glAttachShader(shader_program_id, vertex_shader_id));
    GLCall(glAttachShader(shader_program_id, fragment_shader_id));
    GLCall(glLinkProgram(shader_program_id));
    // Check if shader program linking is a success..
    int success;
    char infoLog[512];
    GLCall(glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success));
    if (!success)
    {
        GLCall(glGetProgramInfoLog(shader_program_id, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
        exit(-1);
    }

    // Delete shaders once we link them
    GLCall(glDeleteShader(vertex_shader_id));
    GLCall(glDeleteShader(fragment_shader_id));
    return shader_program_id;
}
unsigned int Shader::compileShader(ShaderType type, const std::string &file_path)
{

    GLCall(unsigned int shader_id = glCreateShader(type == ShaderType::VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER));
    // 1 - ID of shader
    // 2 - Total number of strings ( only one in this case which is the whole program)
    // 3 - The source file string
    // 4 - NULL
    const char *shader_source = read_file(file_path).c_str();

    GLCall(glShaderSource(shader_id, 1, &shader_source, NULL));
    GLCall(glCompileShader(shader_id));
    // Check if shader compilation is a success..
    int success;
    char infoLog[512];
    GLCall(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GLCall(glGetShaderInfoLog(shader_id, 512, NULL, infoLog));
        std::string shader_type = (type == ShaderType::VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << shader_type << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        exit(-1);
    }

    return shader_id;
}
void Shader::bind() const
{
    GLCall(glUseProgram(m_shader_program_id));
}
void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

int Shader::getUniformLocation(const std::string &uniform_name)
{
    if (m_uniform_location_cache.find(uniform_name) != m_uniform_location_cache.end())
    {
        // Found location already!
        return m_uniform_location_cache[uniform_name];
    }
    GLCall(int location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str()));
    if (location == -1)
    {
        std::cout << "Shader::getUniformLocation failed trying to fetch : " << uniform_name << std::endl;
        exit(-1);
    }
    m_uniform_location_cache[uniform_name] = location;
    return location;
}

void Shader::setUniform4f(const std::string &uniform_name, glm::vec4 vector)
{
    GLCall(glUniform4f(getUniformLocation(uniform_name), vector.r, vector.g, vector.b, vector.a));
}

void Shader::setUniform1i(const std::string &uniform_name, int value)
{
    GLCall(glUniform1i(getUniformLocation(uniform_name), value));
}