#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 u_mvp;

out vec2 v_texCoord;
void main()
{
    u_mvp;
    gl_Position = u_mvp*vec4(position, 1.0);
    v_texCoord = texCoord;
}