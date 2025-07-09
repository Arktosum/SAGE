#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

  
out vec3 ourColor; // output a color to the fragment shader

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP*vec4(aPos, 1.0);
    ourColor = aPos; // set ourColor to the input color we got from the vertex data
} 