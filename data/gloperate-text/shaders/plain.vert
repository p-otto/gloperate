#version 330

layout (location = 0) in vec3 in_origin;
layout (location = 2) in vec3 in_uv;

uniform mat4 modelViewProjection;

out vec2 v_uv;

void main()
{
    v_uv = in_uv.rg;
    gl_Position = modelViewProjection * vec4(in_origin, 1.0);
}
