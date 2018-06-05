#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec2 Min=vec2(-1,-1);
uniform vec2 Max=vec2(1,1);

void main()
{
    mat4 scale = mat4(vec4((Max.x-Min.x),0,0,0),
		      vec4(0,(Max.y-Min.y),0,0),
		      vec4(0,0,0,0),
                      vec4(0,0,0,1)
			);
    mat4 transf = mat4(vec4(1,0,0,-Min.x),
			vec4(0,1,0,-Min.y),
			vec4(0,0,0,0),
			vec4(0,0,0,1)
			);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * transf * scale * vec4(texCoord.s,texCoord.t,0, 1.0);
}
