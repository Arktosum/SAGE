#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float u_time;

void main()
{
    FragColor = vec4(1.0,(1+sin(2*u_time))/2,(1+cos(2*u_time))/2, 1.0);
}