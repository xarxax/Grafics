#version 330 core

in vec2 st;
in vec4 frontColor;
out vec4 fragColor;

uniform float smoothness = 25.0;
uniform sampler2D heightMap;
uniform mat3 normalMatrix;

void main()
{
    float eps = 1.0/128;
    vec3 O = texture(heightMap, st).xyz;
    vec3 X = texture(heightMap, st + vec2(eps, 0.0)).xyz - O;
    vec3 Y = texture(heightMap, st + vec2(0.0, eps)).xyz - O;
    vec3 G = cross(X,Y);
    vec3 N = normalMatrix*normalize(vec3(-G.x, -G.y, smoothness));
    fragColor = vec4(N.z);
}
