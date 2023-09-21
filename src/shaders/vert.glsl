#version 330 core

layout(location = 0) in vec3 inPosition;  // Vertex position input
out vec4 vertexColor;  // Output color

void main() {
    // Transform the vertex position
    gl_Position = vec4(inPosition, 1.0);

    // Assign a color (e.g., red)
    vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
}