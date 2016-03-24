#version 330

layout (location = 0) in vec3 in_origin;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_uv;

uniform mat4 modelViewProjection;

out vec2 v_uv;
out vec3 v_normal;

void main()
{
    v_uv = in_uv.rg;
    v_normal = in_normal;
    gl_Position = modelViewProjection * vec4(in_origin, 1.0);
}
