#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
    if (gl_PrimitiveIDIn == 0) {
        float R = distance(boundingBoxMax, boundingBoxMin)/2;
        vec4 cyan = vec4(0.0,1.0,1.0,0.0);
        vec2 xzpoints[5];
        xzpoints[0] = vec2(-R,-R);
        xzpoints[1] = vec2(R,-R);
        xzpoints[2] = vec2(-R,R);
        xzpoints[3] = vec2(R,R);
        for( int i = 0 ; i < 4 ; i++ )
	    {
		    gfrontColor = cyan;
		    gl_Position = vec4(xzpoints[i][0], boundingBoxMin.y-0.01, xzpoints[i][1],1.0);
		    gl_Position = modelViewProjectionMatrix * gl_Position;
		    EmitVertex();
	    }
        EndPrimitive();
    }
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0.0);
        gl_Position = gl_in[i].gl_Position;
        gl_Position.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
