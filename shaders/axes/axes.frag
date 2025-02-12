#version 330 core
layout(location= 0) out vec4 FragColor;

in vec3 v_pos;
void main()
{
    FragColor = vec4(v_pos,1.0);
}