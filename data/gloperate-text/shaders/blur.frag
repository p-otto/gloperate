#version 330

in vec2 v_uv;

uniform sampler2D u_normal;
uniform sampler2D u_occlusion;
uniform vec2 direction;

layout(location = 0) out vec4 occlusion;

#define EPSILON 0.001
#define COMP_NORMAL 0.5

const int kernelSize = 5;

void main()
{
    vec3 normal = texture(u_normal, v_uv).rgb;

    vec2 stepSize = vec2(1.0) / textureSize(u_occlusion, 0);

    occlusion = vec4(1.0);
    occlusion.x = 0.0;
    float count = 0.0;
    for (int i = -kernelSize; i <= kernelSize; ++i)
    {
        vec2 cur_uv = v_uv + vec2(stepSize) * direction * i;
        vec3 cur_normal = texture(u_normal, cur_uv).rgb;

        occlusion.x += texture(u_occlusion, cur_uv).r;
        count += 1.0;
    }
    occlusion.x /= count;
}
