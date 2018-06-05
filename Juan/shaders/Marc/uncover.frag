#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform float time;
in float NDSx;

void main()
{
	fragColor = vec4(step(-1+time,NDSx),step(-1+time,NDSx),1,0);
}
