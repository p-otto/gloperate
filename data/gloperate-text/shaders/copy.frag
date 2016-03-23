#version 330

uniform sampler2D glyphs;

in vec2 g_uv;

layout (location = 0) out vec4 out_color;

void main()
{
    float val = texture(glyphs, g_uv).r;
    out_color = vec4(vec3(val),1.0);
}
