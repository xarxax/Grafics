#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform mat3 normalMatrix;

uniform float time;
uniform float amplitude = 0.1;
uniform float freq = 1;
const float PI = 3.141592;

void main()
{
    float d = amplitude*sin(2*PI*freq*time);
    gl_Position = modelViewProjectionMatrix*vec4(vertex + d*normal, 1.0);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);
}

/* Esta es mi version inicial porque interpreté que "abans de transformar el vertex a clip space"
 significa just abans, i.e.: cuando el vertex esta en eye space. Pero Gerard lo aplicaba en object space...
 Els dos fan el mateix (millor el més simple) i, de fet, sempre transformem a clip space directament desde object.

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    float d = amplitude*sin(2*PI*freq*time);
    vec4 v2 = modelViewMatrix*vec4(vertex, 1.0) + vec4(vec3(N*d),0.0);
    gl_Position = projectionMatrix*v2;
    frontColor = vec4(N.z);
}

*/


