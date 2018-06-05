#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{ 
    vec3 color = vec3(1.0);
    vec2 center = vec2(0.5, 0.5);
    if (distance(center, vtexCoord) <= 0.2)
        color = vec3(1.0, 0.0, 0.0);
    fragColor = vec4(color, 1.0);
}
