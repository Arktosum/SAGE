#version 330 core
out vec4 FragColor;
<<<<<<< HEAD

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
}
=======

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
>>>>>>> parent of ba2480e (opengl : modularized vao,vbo,ebo,shader)
