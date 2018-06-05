#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
in vec2 vtexCoord; 


void main()
{
   float n = 9;
   int x = int(floor(fract(vtexCoord.s)*n));
   if(x%2 ==0) fragColor = vec4(vec3(1,1,0),1);
   else fragColor = vec4(vec3(1,0,0),1);
}
