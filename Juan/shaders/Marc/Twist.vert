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

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    float theta = 0.4*vertex.y*sin(time);
    mat4 rotacio = mat4(vec4(cos(-theta),0,sin(-theta),0.),
			vec4(0,1,0,0.),
			vec4(-sin(-theta),0,cos(-theta),0.),
			vec4(0.,0.,0.,1.)
			);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * rotacio * vec4(vertex, 1.0);
}
