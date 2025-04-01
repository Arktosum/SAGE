#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

uniform mat4 u_proj;
// uniform vec2 u_mousePos;
// uniform vec2 u_viewport;

void main()
{
   gl_Position = u_proj*vec4(aPos, 1.0);
} 