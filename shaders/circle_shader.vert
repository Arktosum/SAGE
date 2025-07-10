#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 u_mvp;

out vec3 localPos;
void main() {
    gl_Position = u_mvp * vec4(aPos, 1.0);
    localPos=aPos;
}
