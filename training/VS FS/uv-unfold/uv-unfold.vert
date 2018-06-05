#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform vec2 Min= vec2(-1,-1);
uniform vec2 Max= vec2(1,1);

uniform mat4 modelViewProjectionMatrix;


void main()
{	
    
    frontColor =vec4(color,1.0);


   vec2 diagonal = Max-Min;
//mirem la situacio respecte al mínim    
vec2 relativecoord= texCoord- Min;
    //normalitzem a 1
vec2 normalized= vec2(relativecoord.s/diagonal.s, relativecoord.t/diagonal.t);
//fem que encaixi amb la llargada del viewport
vec2 final = 2*normalized - diagonal/2;
    gl_Position =  vec4(final,0, 1.0);
}
