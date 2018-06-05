#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time=0;
const float PI = 3.14159;


uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform bool eyespace;

float sinusoidal(float x, float amplitude ) {
	return sin(x)*amplitude;
}
void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.);
    vtexCoord = texCoord;
    float y;
    if(eyespace)y = (modelViewMatrix * vec4(vertex,1)).y;
    else y = vertex.y;
    float d = length(boundingBoxMax-boundingBoxMin) * y/20 ;
    vec3 new_vertex= vertex+ sinusoidal(time,d)*normal;
    gl_Position = modelViewProjectionMatrix * vec4(new_vertex, 1.0);
}
