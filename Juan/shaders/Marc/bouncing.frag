#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in float Nz;
void main()
{
    fragColor = frontColor;
}
