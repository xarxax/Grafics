#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform vec3 groc = vec3(1.0,1.0,0.0);
uniform vec3 vermell = vec3(1.0,0.0,0.0);

void main()
{
    vec3 color;
    float fractS = fract(vtexCoord.s);
    if (mod(fractS*9,2.0) < 1.0) color = groc;
    else color = vermell;
    fragColor = vec4(color, 1.0);
}

