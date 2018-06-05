#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
uniform sampler2D skeleton;
in vec2 vtexCoord; 

uniform float time=0 ;
uniform float FPS = 30;
uniform int tiles=5;

void main()
{
  int  xlen= 44;
  int frame = int(mod(time *FPS,xlen));
  vec2 escala = vec2((frame+vtexCoord.s*tiles)/44,vtexCoord.t*tiles);
  vec4 color = texture(skeleton, escala);
  fragColor = vec4(1.)-color;
}
