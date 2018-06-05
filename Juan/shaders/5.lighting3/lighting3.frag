#version 330 core

in vec3 vert;
in vec3 norm;
in vec4 frontColor;
out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;

uniform vec4 lightAmbient; 	//similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse; 	//similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;	//similar a gl_LightSource[0].specular
uniform vec4 lightPosition;	//similar a gl_LightSource[0].position
							//(sempre estarà en eye space)

uniform vec4 matAmbient; 	//similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse; 	//similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular; 	//similar a gl_FrontMaterial.specular
uniform float matShininess; //similar a gl_FrontMaterial.shininess

vec4 light(vec3 N, vec3 V, vec3 L)
{
	N = normalize(N);
	V = normalize(V);
	L = normalize(L);
	vec3 H = normalize(V+L);
	float NdotL = max( 0.0, dot( N,L ) );
	float NdotH = max( 0.0, dot( N,H ) );
	float Idiff = NdotL;
	float Ispec = 0;
	if (NdotL>0) Ispec=pow( NdotH, matShininess );
	return	matAmbient * lightAmbient +
			matDiffuse * lightDiffuse * Idiff+
			matSpecular * lightSpecular * Ispec;
}


void main()
{
	vec3 P = vert;
	vec3 N = normalize(norm);
	vec3 V = vec3(0.0, 0.0, 1.0);
	vec3 L = lightPosition.xyz-P;
	fragColor = light(N, V, L);
}

