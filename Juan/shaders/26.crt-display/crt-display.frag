#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n=1;

void main()
{
    vec2 pos = gl_FragCoord.xy - vec2(0.5, 0.5);
    int y = int(pos.y);
    if (y % n != 0) discard;
    fragColor = frontColor;
}
