#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main()
{
    float x = vtexCoord.s*n;
    float y = vtexCoord.t*n;
    vec3 color;
    if ((x - floor(x) < 0.1) || (y - floor(y) < 0.1)) color = vec3(0.0);
    else color = vec3(0.8);
    fragColor = vec4(color, 1.0);
}


