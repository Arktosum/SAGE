#version 330 core

layout(location = 0) in vec3 inPosition;  // Vertex position input

out vec3 aPos;


// for all c in plane, zn+1 = zn^2 + c  z0 = 0 , n = 0 to inf ,and zn+1 < 100



void main() {
    gl_Position = vec4(inPosition, 1.0);
    aPos = inPosition;
}

