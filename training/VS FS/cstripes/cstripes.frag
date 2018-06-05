#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
in vec2 vtexCoord; 
uniform int nstripes = 9;
uniform vec2 origin;


void main()
{ 
   float interval= length (vtexCoord- origin);
   if(int(floor(interval*nstripes))%2==0) fragColor = vec4(1,0,0,1);
   else fragColor = vec4(1,1,0,1);
}
