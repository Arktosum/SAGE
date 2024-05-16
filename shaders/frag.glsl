#version 330 core

layout (location = 0) out vec4 FragColor;  
uniform float u_time;
// uniform vec2 mouse;

in vec3 aPos;
void main() {
    FragColor = vec4(
        (sin(aPos.x + u_time) + 1.0) / 2.0,
        (cos(aPos.y + u_time) + 1.0) / 2.0,
        (cos(aPos.x + aPos.y + u_time) + 1.0) / 2.0,
        1.0);
}
