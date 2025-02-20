#version 330 core
layout(location= 0) out vec4 FragColor;

in vec3 v_pos;
flat in int v_instance_id;

uvec3 hash3(int x) {
    uint ux = uint(x);  // Explicit conversion
    ux ^= ux >> 16;
    ux *= 0x7feb352du;
    ux ^= ux >> 15;
    ux *= 0x846ca68bu;
    ux ^= ux >> 16;
    return uvec3(ux, ux * 48271u, ux * 65497u);
}
void main()
{
    uvec3 randNums = hash3(v_instance_id);
    // float r = float(int(randNums.x) % 255) / 255.0;
    // float g = float(int(randNums.y) % 255) / 255.0;
    // float b = float(int(randNums.z) % 255) / 255.0;

    float r = float(((v_instance_id * 11)% 255)/255.0);
    float g = float(((v_instance_id * 13)% 255)/255.0);
    float b = float(((v_instance_id * 17)% 255)/255.0);
    FragColor = vec4(r,g,b,1.0);
}