#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

vec3 getYRotation(vec3 v, float phi) {
    float seno = sin(phi);
    float coseno = cos(phi);
    mat3 yrot = mat3(vec3(coseno, 0.0, -seno),
	vec3(0.0, 1.0, 0.0),
	vec3(seno, 0.0, coseno));
    return yrot*v;
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(0.0, 0.0, 1.0,1.0);
    vtexCoord = texCoord;

    float phi = -time*vtexCoord.s;
    gl_Position = modelViewProjectionMatrix * vec4(getYRotation(vertex, phi), 1.0);
}
