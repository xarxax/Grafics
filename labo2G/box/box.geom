#version 330 core
        
layout(triangles) in;
layout(line_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

//added
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
const vec4 BLACK=vec4(0, 0, 0, 1);

void boxVertex(float x, float y,float z){
   gfrontColor=BLACK;
  gl_Position=modelViewProjectionMatrix*vec4(vec3(x,y,z), 1);
EmitVertex();

}

void main( void )
{
       

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	//background
	if (gl_PrimitiveIDIn == 0) {
          boxVertex(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMin.z);
          boxVertex(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMin.z);
          boxVertex(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMax.z);
          boxVertex(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMax.z);
          boxVertex(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMin.z);
          boxVertex(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMin.z);
          boxVertex(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMin.z);
          boxVertex(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMax.z);
          boxVertex(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMax.z);
          boxVertex(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMin.z);
          boxVertex(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMin.z);
          boxVertex(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMin.z);
          boxVertex(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMin.z);
          boxVertex(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMax.z);
          boxVertex(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMax.z);
          boxVertex(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMax.z);
          boxVertex(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMax.z);

    EndPrimitive();
    	}



}
