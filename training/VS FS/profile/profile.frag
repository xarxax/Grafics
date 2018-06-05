#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
in vec3 N;
in vec3 P;
vec4 DARK_YEL= vec4(0.7,0.6,0.,1);
uniform float epsilon=0.1;
uniform float light=0.5;

void main()
{
  float c=abs(length(dot(normalize(P), normalize(N))));
  if (c<epsilon) fragColor=DARK_YEL;
  else fragColor=(frontColor*light)*N.z;
}
