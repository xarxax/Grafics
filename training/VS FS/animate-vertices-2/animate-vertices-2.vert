#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

const float PI = 3.14159;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amplitude= 0.1;
uniform float freq=1;
uniform float time=0;

float sinusoidal(float x) {
	float fase = 2*PI*texCoord;//texCoord.s
	return sin(x*(2*PI *freq)+fase)*amplitude;
}

void main()
{
    float dist= sinusoidal(time);
    vec3 new_vert= vertex+dist*normal;
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(1.0) * N.z;
    gl_Position = modelViewProjectionMatrix * vec4(new_vert, 1.0);
}
