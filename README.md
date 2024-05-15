# SAGE

A Graphics Renderer made using OpenGL and GLFW and GLaD


## Usage
cd src

g++ -o main.exe glad.c window.cpp shader.cpp VBO.cpp IBO.cpp main.cpp -L../lib -lglfw3 -lopengl32 -lgdi32 && main



# Vertex

A vertex contains many attributes such as
- position
- color
- texture
- normal etc..

vertex attribute pointers tell the layout of the data in our VBO
index - index of any given attribute

the index can be then used in the shader to get that attribute. ( layout = 0,1,2..15)

NOTE : we can have at most 16 attributes in a vertex.
