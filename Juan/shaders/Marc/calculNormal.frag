#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 coord;

void main()
{
    vec3 tgx = dFdx(coord);
    vec3 tgy = dFdy(coord);
    vec3 N = normalize(cross(tgx,tgy));
    fragColor = frontColor*N.z;
    
}
