#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in mat4 a_model;     // Per-instance model matrix

// uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 v_pos;
flat out int v_instance_id;
void main()
{
    // gl_Position = u_projection * u_view *u_model * vec4(aPos, 1.0);
    gl_Position = u_projection * u_view * a_model * vec4(aPos, 1.0);
    // gl_Position = vec4(aPos, 1.0);
    v_pos = aPos;
    v_instance_id = gl_InstanceID;
}