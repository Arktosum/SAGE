#version 330 core
layout(location= 0) out vec4 FragColor;

uniform vec3 u_lightColor;
void main()
{
    FragColor = vec4(u_lightColor,1.0);
}