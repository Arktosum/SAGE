#version 330 core
out vec4 FragColor;  
  
uniform vec2 u_mousePos;
uniform vec2 u_viewport;

void main()
{
   FragColor = vec4(u_mousePos/u_viewport,0.0f,1.0);
}