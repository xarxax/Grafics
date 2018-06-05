#version 330 core

in vec4 frontColor;
out vec4 fragColor;


//added

in vec3 P;
in vec3 N;

uniform mat4 modelViewMatrixInverse;

uniform float time=0;
uniform bool rotate=true;


// V, N, P, lightPos han d'estar al mateix espai de coordenades
// V és el vector unitari cap a l'observador
// lightPos és la posició de la llum
// lightColor és el color de la llum


vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos, vec3 lightColor) {
	const float shininess=100.0;
	const float Kd=0.5;
	N=normalize(N);
	vec3 L=normalize(lightPos-P);
	vec3 R=reflect(-L, N);
	float NdotL=max(0.0, dot(N, L));
	float RdotV=max(0.0, dot(R, V));
	float spec=pow(RdotV, shininess);
	return vec4(Kd*lightColor*NdotL+vec3(spec), 0);
}

void main()
{	
  //P vertex in world space
  //N normal in world space
  vec3 V=normalize(modelViewMatrixInverse[3].xyz-P);
 //the 4 lights
  vec3 L1=vec3(0, 10, 0);
  vec3 L2=vec3(0, -10, 0);
  vec3 L3=vec3(10, 0, 0);
  vec3 L4=vec3(-10, 0, 0);
  if (rotate) {
//matrix specified in the exercise
    mat3 R=mat3(vec3(cos(time), sin(time), 0), 
      vec3(-sin(time), cos(time), 0), 
      vec3(0, 0, 1));
//apply rotation
    L1=R*L1;
    L2=R*L2;
    L3=R*L3;
    L4=R*L4;
  }
//change from eyespace to world space
  L1=(modelViewMatrixInverse*vec4(L1, 1)).xyz;
  L2=(modelViewMatrixInverse*vec4(L2, 1)).xyz;
  L3=(modelViewMatrixInverse*vec4(L3, 1)).xyz;
  L4=(modelViewMatrixInverse*vec4(L4, 1)).xyz;
//calculate the illumination from every light in every point 
  fragColor=light(V, N, P, L1, vec3(0, 1, 0))
    +light(V, N, P, L2, vec3(1, 1, 0))
    +light(V, N, P, L3, vec3(0, 0, 1))
    +light(V, N, P, L4, vec3(1, 0, 0));
}
