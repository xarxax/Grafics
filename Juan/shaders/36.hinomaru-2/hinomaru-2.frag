#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const vec4 blanc = vec4(1.0,1.0,1.0,1.0);
const vec4 vermell = vec4(1.0,0.0,0.0,1.0);
const vec2 centre = vec2(0.5,0.5);
const float phi = 3.141592/16;

uniform bool classic=true;

void main()
{
    if (distance(vtexCoord,centre) <= 0.2) fragColor = vermell;
    else if (classic) {
        vec2 u = vtexCoord - centre;
        float theta = atan(u.t,u.s);
        if (mod(theta/phi + 0.5, 2) < 1)
            fragColor = vermell;
        else fragColor = blanc;
    }
    else fragColor = blanc;
        
}
