#version 330 core

in vec3 vert;
in vec4 frontColor;
out vec4 fragColor;

void main()
{
	vec3 X = dFdx(vert);
	vec3 Y = dFdy(vert);
	vec3 normal = normalize(cross(X,Y));
    fragColor = frontColor * normal.z;
}
