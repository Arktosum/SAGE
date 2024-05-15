#version 330 core

layout (location = 0) out vec4 FragColor;  
uniform float u_time;
in vec3 aPos;
int maxn = 1000; // Increased max iterations for better resolution

vec3 iterationColor(int n) {
    float t = float(n)/float(maxn);
    vec3 colorA = vec3(0.0f,0.0f,0.0f);
    vec3 colorB = vec3(1.0f,1.0f,1.0f);
    return mix(colorA, colorB, t);
}

int mandelbrot(float x, float y) {
    float znx = 0.0;
    float zny = 0.0;
    float zx, zy; 
    float cx = x;
    float cy = y;
    float threshold = 4.0; // (squared magnitude)

    for (int i = 0; i < maxn; i++) {
        zx = znx * znx - zny * zny + cx;
        zy = 2.0 * znx * zny + cy;

        znx = zx;
        zny = zy;

        if ((znx * znx + zny * zny) > threshold) {
            return i; // Return the number of iterations before escape
        }
    }
    return maxn; // Return max iterations if it didn't escape
}


void main() {
    int n = mandelbrot(aPos.x,aPos.y);
    vec3 finalColor = iterationColor(n);
    FragColor = vec4(finalColor,1.0f);
    // FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}
