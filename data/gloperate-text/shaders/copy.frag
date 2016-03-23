#version 330

uniform sampler2D glyphs;

in vec2 g_uv;

layout (location = 0) out vec4 out_color;

void main()
{
    out_color = vec4(vec3(texture(glyphs, g_uv).r),1.0);
}
