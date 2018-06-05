#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

//added 
uniform mat4 modelViewProjectionMatrix;

uniform float time = 0;

void main(void) {
  float N=time*100 ;
  if(float(gl_PrimitiveIDIn) < N){
	  for (int i=0; i<3; ++i) { 
	    gfrontColor=vfrontColor[i]; 
	    gl_Position=modelViewProjectionMatrix*gl_in[i].gl_Position;
	    EmitVertex();
	  }
	  EndPrimitive();
  }

}

