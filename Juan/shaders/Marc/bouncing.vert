#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out float Nz;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

uniform float time;

uniform float scale=8;
const vec3 TO = vec3(-1,-1,0);
const vec3 V = vec3(2,2,0);

float triangleWave(float x) {
 	return abs(mod(x, 2) - 1.0);
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vtexCoord = texCoord;
    vec3 t = vec3 (triangleWave(time/1.618), triangleWave(time),0);
    vec3 T = scale*(TO+vec3(V.x*t.x,V.y*t.y,1));
    mat4 Tmatrix = mat4(
			vec4(1,0,0,T.x),
			vec4(0,1,0,T.y),
			vec4(0,0,1,0),
			vec4(0,0,0,1)
			); 
    frontColor = vec4(0.3, 0.3, 0.9, 1.0)*abs(N.z);
    vec4 coordTrans = vec4((T.x+vertex.x)/scale,(T.y+vertex.y)/scale,vertex.z/scale, 1.0);
    vec4 prova = vec4(T,1.0) * (vec4(N,1.0));
    gl_Position = modelViewProjectionMatrix * coordTrans;
}
