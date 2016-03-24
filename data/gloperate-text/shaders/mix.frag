#version 330

in vec2 v_uv;

uniform sampler2D colorTexture;
uniform sampler2D occlusionTexture;

out vec4 out_color;

void main()
{
    vec3 color = texture(colorTexture, v_uv).rgb;
    float occlusion = texture(occlusionTexture, v_uv).r;
    occlusion = 1.0;
    out_color = vec4(color * occlusion, 1.0);
}
