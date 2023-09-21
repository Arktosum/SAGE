#version 330 core

in vec4 vertexColor;  // Input color
out vec4 FragColor;  // Output color

void main() {
    // Use the color from the vertex shader as the final color
    FragColor = vertexColor;
}