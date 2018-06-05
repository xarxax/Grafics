#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//added
uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;
in vec2 vtexCoord; 

uniform float time=0 ;
uniform float slice = 0.1;

void main()
{
    float fase= mod(time,4*slice);
    vec2 new_vtexCoord = vec2(0.0,5./6);
    vec4 color;
    if(fase< slice) color = texture(sampler0, vtexCoord);
    else if(fase< slice*2 )color = texture(sampler1, vtexCoord);
    else if(fase< slice*3 )color = texture(sampler2, vtexCoord);
    else color = texture(sampler3, vtexCoord);
    fragColor = color*color.a;
}
