#version 330 core

layout(location = 0) in vec3 inPosition;  // Vertex position input
uniform mat4 u_matrix;
out vec3 aPos;


void main() {
    gl_Position = u_matrix*vec4(inPosition, 1.0);
    aPos = inPosition;
}

