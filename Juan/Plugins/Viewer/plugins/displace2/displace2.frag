#version 330 core

in vec3 vert;
in vec4 frontColor;
out vec4 fragColor;
uniform float smoothness = 25.0;

void main()
{
    vec3 X = dFdx(vert);
    vec3 Y = dFdy(vert);
    vec3 N = cross(X,Y);
    N = normalize(vec3(-N.x, -N.y, smoothness));
    fragColor = vec4(N.z);
}
