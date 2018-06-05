#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main()
{
    int x = int(floor(vtexCoord.s*n));
    int y = int(floor(vtexCoord.t*n));
    vec3 color;
    if ((x+y) % 2 != 0) color = vec3(0.0);
    else color = vec3(0.8);
    fragColor = vec4(color, 1.0);
}

