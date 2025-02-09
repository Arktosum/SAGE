#version 330 core
layout (location = 0) in vec3 aPos;
<<<<<<< HEAD
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
=======

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
>>>>>>> parent of ba2480e (opengl : modularized vao,vbo,ebo,shader)
}