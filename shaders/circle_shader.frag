#version 330 core
out vec4 FragColor;
uniform vec3 u_color;

in vec3 localPos;
uniform vec2 u_center;
uniform float u_radius;
void main() {
    float dist = distance(localPos.xy,u_center);
    if(dist > u_radius){
        discard;
    }
    FragColor = vec4(u_color, 1.0);
}

