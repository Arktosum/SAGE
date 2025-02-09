#version 330 core
layout(location= 0) out vec4 FragColor;

in vec2 v_texCoord;
uniform sampler2D u_texture;
uniform vec4 u_color;
void main()
{
    vec4 texColor = texture(u_texture,v_texCoord);
    FragColor = texColor;
} 