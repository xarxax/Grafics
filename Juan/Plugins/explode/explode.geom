#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main( void )
{
    float step = 0.1;
    vec3 points[30];
    vec3 center = vec3(0);
    vec4 color = vfrontColor[0];
    for( int i = 0 ; i < 3 ; i++ )
	{
		center += gl_in[i].gl_Position;
	}
    center /= 3;
        
    //Left
    points[0] = vec3(-step, -step, -step);
    points[1] = vec3(-step, +step, -step);
    points[2] = vec3(-step, +step, +step);
    points[3] = vec3(-step, +step, +step);
    points[4] = vec3(-step, -step, +step);

    //Right
    points[5] = vec3(+step, -step, -step);
    points[6] = vec3(+step, +step, -step);
    points[7] = vec3(+step, +step, +step);
    points[8] = vec3(+step, +step, +step);
    points[9] = vec3(+step, -step, +step);

    //Front
    points[10] = vec3(-step, -step, +step);
    points[11] = vec3(-step, +step, +step);
    points[12] = vec3(+step, -step, +step);
    points[13] = vec3(+step, -step, +step);
    points[14] = vec3(+step, +step, +step);

    //Back
    points[15] = vec3(-step, -step, -step);
    points[16] = vec3(-step, +step, -step);
    points[17] = vec3(+step, -step, -step);
    points[18] = vec3(-step, -step, -step);
    points[19] = vec3(+step, +step, -step);

    //Top
    points[20] = vec3(-step, +step, -step);
    points[21] = vec3(+step, +step, -step);
    points[22] = vec3(-step, +step, +step);
    points[23] = vec3(-step, +step, +step);
    points[24] = vec3(+step, +step, +step);

    //Bottom
    points[20] = vec3(-step, -step, -step);
    points[21] = vec3(+step, -step, -step);
    points[22] = vec3(-step, -step, +step);
    points[23] = vec3(-step, -step, +step);
    points[24] = vec3(+step, -step, +step);

	for( int i = 0 ; i < 30; i++ )
	{
		gfrontColor = color;
		gl_Position = modelViewProjectionMatrix * (center + points[i]);
		EmitVertex();
	}
    EndPrimitive();
}