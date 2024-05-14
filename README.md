# SAGE

A Graphics Renderer made using OpenGL and GLFW and GLaD

- #include "../include/glad/glad.h"
- #include "../include/GLFW/glfw3.h"

## Usage
cd src

g++ -o main.exe glad.c main.cpp -L../lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 && main
