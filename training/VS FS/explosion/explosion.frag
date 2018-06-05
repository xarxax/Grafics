#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
uniform sampler2D explosion;
in vec2 vtexCoord; 

uniform float time=0 ;
uniform float FPS = 30;

void main()
{
  int  xlen= 8, ylen=6;

  int frame = int(time *FPS) % 48;
  int x= frame%8, y= (frame/8) %6;

 vec2 new_vtexCoord = vec2(0.0,5./6);
    new_vtexCoord += vec2((vtexCoord.s + x)/8, (vtexCoord.t - y)/6);
    vec4 color = texture(explosion, new_vtexCoord);
    fragColor = color*color.a;
}
