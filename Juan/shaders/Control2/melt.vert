#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax; 
uniform float time=1;

void main()
{   
    vec3 C = (boundingBoxMax+boundingBoxMin)/2.0;
    float d = distance(vertex.xz, C.xz);
    vec3 new_V = vertex;

    new_V.y = vertex.y - time*(0.5+0.1*pow(d, 1.2));
    
    float offset = new_V.y - boundingBoxMin.y;
    if (offset < 0) {
	new_V.y = boundingBoxMin.y + 0.2*offset;
	vec2 xz_offset = -0.1*time*offset*normalize(normalMatrix * normal).xz;
	new_V.xz -= xz_offset;
    }
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    gl_Position = modelViewProjectionMatrix * vec4(new_V, 1.0);
}
