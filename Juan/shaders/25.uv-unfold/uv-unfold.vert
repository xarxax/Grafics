#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform vec2 Min=vec2(-1,-1);
uniform vec2 Max=vec2(1,1);

void main()
{
    frontColor = vec4(color,1.0);

    vec2 lengths= Max-Min;  
    vec2 coord1 = texCoord-Min;                                     // coord relevantes entre [0,length]
    vec2 coord2 = vec2(coord1.s/lengths.s, coord1.t/lengths.t);     // coord relevantes entre [0,1]
    vec2 coord3 = 2*coord2 - vec2(1);                               // coord relevantes entre [-1,1]
    gl_Position = vec4(coord3,0,1);
}

