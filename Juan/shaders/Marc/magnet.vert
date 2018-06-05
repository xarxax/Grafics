#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrixInverse;
uniform mat4 modelMatrixInverse;
uniform mat3 normalMatrix;
uniform vec4 lightPosition; 
uniform float n=4;

void main()
{ 
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(1.0) * N.z;
    vtexCoord = texCoord;

    vec4 F = modelViewMatrixInverse * lightPosition;
    float w = clamp(1/pow(distance(vertex,F.xyz),n),0,1);
    vec3 new_vertex = (1.0-w)*vertex + w*F.xyz; 

    gl_Position = modelViewProjectionMatrix * vec4(new_vertex,1.0);
}
