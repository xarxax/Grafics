#version 330 core

in vec3 N;
in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D window;
uniform sampler2D interior1; // observeu el digit 1 al final
uniform sampler2D exterior2; // observeu el digit 2 al final


void main()
{
    vec4 C = texture(window, vtexCoord);
    if (C[3] == 1) {
        fragColor = C;
    }
    else {
        vec4 D = texture(interior1, vtexCoord+0.5*N.xy);
        if (D[3] == 1) {
            fragColor = D;
        }
        else {
            fragColor = texture(exterior2, vtexCoord+0.7*N.xy);
        }
    }
}
