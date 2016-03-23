#version 330

uniform sampler2D glyphTexture;

in vec2 v_uv;

layout (location = 0) out vec4 out_color;

float aastep(float t, float value)
{
	//float afwidth = length(vec2(dFdx(value), dFdy(value))) * 1.0;
	float afwidth = fwidth(value) * 1.0;
	return smoothstep(t - afwidth, t + afwidth, value);
}

float tex(float t, vec2 uv)
{
	return aastep(t, texture(glyphTexture, uv).r);
}

float aastep4x4s(float t, vec2 uv)
{
	float x1 = dFdx(uv.x) * 1.0 / 8.0;
	float y1 = dFdy(uv.y) * 1.0 / 8.0;
	float x2 = dFdx(uv.x) * 3.0 / 8.0;
	float y2 = dFdy(uv.y) * 3.0 / 8.0;

	float v = tex(t, uv + vec2(-x2,-y2))
	        + tex(t, uv + vec2(-x2,-y1))
	        + tex(t, uv + vec2(-x2,+y1))
	        + tex(t, uv + vec2(-x2,+y2))

	        + tex(t, uv + vec2(-x1,-y2))
	        + tex(t, uv + vec2(-x1,-y1))
	        + tex(t, uv + vec2(-x1,+y1))
	        + tex(t, uv + vec2(-x1,+y2))

	      	+ tex(t, uv + vec2(+x1,-y2))
	        + tex(t, uv + vec2(+x1,-y1))
	        + tex(t, uv + vec2(+x1,+y1))
	        + tex(t, uv + vec2(+x1,+y2))

	        + tex(t, uv + vec2(+x2,-y2))
	        + tex(t, uv + vec2(+x2,-y1))
	        + tex(t, uv + vec2(+x2,+y1))
	        + tex(t, uv + vec2(+x2,+y2));

	return v / 16.0;
}

void main()
{
    vec2 uv = vec2(1.0)-v_uv.ts;

    float s = texture(glyphTexture, uv).r;
    //if(s < 0.4)
    //    discard;

    float a = aastep4x4s(0.5, uv);
    out_color = vec4(vec3(1.0-a), 1.0);
}
