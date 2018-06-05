#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D map;
uniform float time;
uniform float a=0.5;

const float PI = 3.141592;

void main()
{
    vec4 color = texture(map,vtexCoord);
    float m = max(color.x, max(color.y, color.z));
    vec2 u = vec2(m,m);
    float theta = 2*PI*time;
    mat2 rotationMatrix = mat2(cos(theta), -sin(theta),
                               sin(theta),  cos(theta));
    vec2 u_ = rotationMatrix*u;
    vec2 offset = (a/100.0)*u_;
    fragColor = texture(map, vtexCoord+offset);
}
