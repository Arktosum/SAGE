#pragma once
#include <glad/glad.h>

#define ASSERT(x) \
    if (!(x))     \
    __builtin_trap()

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLCheckError(#x, __LINE__, __FILE__));

void GLClearError();
bool GLCheckError(const char *function, const int line, const char *filepath);
