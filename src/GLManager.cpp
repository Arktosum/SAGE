#include "GLManager.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
std::string intToHex(int num)
{
    std::stringstream ss;
    ss << std::hex << num; // Convert to hexadecimal
    return ss.str();
}

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLCheckError(const char *function, const int line, const char *filepath)
{

    /*

    GL_NO_ERROR 0
    GL_INVALID_ENUM 0x0500
    GL_INVALID_VALUE 0x0501
    GL_INVALID_OPERATION 0x0502
    GL_OUT_OF_MEMORY 0x0505
    */
    while (GLenum error = glGetError())
    {
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "OPENGL ERROR CODE : " << "(0x" << intToHex(error) << ")" << std::endl;
        std::cout << "FUNCTION  : " << function << std::endl;
        std::cout << "LINE  : " << line << std::endl;
        std::cout << "FILEPATH  : " << filepath << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;

        return false;
    }
    return true;
}