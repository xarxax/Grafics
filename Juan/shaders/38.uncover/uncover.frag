#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time=1;

void main()
{
    if (time/2 <= vtexCoord.s) discard;
    fragColor = vec4(0.0, 0.0, 1.0, 1.0); //Blue
}
