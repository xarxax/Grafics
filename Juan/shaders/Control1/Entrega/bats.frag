#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D bat0, bat1;
uniform float time;

void main()
{
    vec4 color;
    vec2 coord = gl_FragCoord.xy/64 - vec2(time);
    if (mod(time, 0.1) < 0.05) {
        color = texture(bat0, coord);
    }
    else {
        color = texture(bat1, coord);
    }
    if (color[3] > 0.2)  {
        fragColor = vec4(0.0);
    }
    else {
        fragColor = frontColor;
    }
}
