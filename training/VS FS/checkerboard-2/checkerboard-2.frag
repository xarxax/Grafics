#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
in vec2 vtexCoord; 
uniform float n = 8;

void main()
{
   int x = int(floor(vtexCoord.s*n));
   int y = int(floor(vtexCoord.t*n));
   if((x+y)%2 !=0) fragColor = vec4(vec3(0),1);
   else fragColor = vec4(vec3(0.8),1);
}
