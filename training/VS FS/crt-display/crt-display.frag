#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n;

void main()
{
    vec2 pos = gl_FragCoord.xy - vec2(0.5, 0.5);
    if(bool(int(pos.y) %n))discard;
    fragColor = frontColor;
}
