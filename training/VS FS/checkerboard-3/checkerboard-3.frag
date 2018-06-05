#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
in vec2 vtexCoord; 
uniform float n = 8;

void main()
{
   float x = (vtexCoord.s*n);
   float y = (vtexCoord.t*n);
   if(x - floor(x) < 0.1 || y- floor(y) < 0.1)  fragColor = vec4(vec3(0),1);
   else fragColor = vec4(vec3(0.8),1);
}
