#version 330

uniform sampler2D glyphs;

in vec2 g_uv;

layout (location = 0) out float out_val;

void main()
{
	out_val = texture(glyphs, g_uv).r;
}
