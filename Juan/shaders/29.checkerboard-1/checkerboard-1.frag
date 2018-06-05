#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    float board_size = 8;
    int x = int(floor(vtexCoord.s*board_size));
    int y = int(floor(vtexCoord.t*board_size));
    vec3 color;
    if ((x+y) % 2 != 0) color = vec3(0.0);
    else color = vec3(0.8);
    fragColor = vec4(color, 1.0);
}
