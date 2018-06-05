 #version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

#define NUM_COLORS 5

void main()
{
    vec4 P=modelViewProjectionMatrix * vec4(vertex, 1.0);
    P = P/P[3];    

    vec3[NUM_COLORS] colors;
    //Init colors
    colors[0] = vec3(1.0,0.0,0.0); //Red
    colors[1] = vec3(1.0,1.0,0.0); //Yellow
    colors[2] = vec3(0.0,1.0,0.0); //Green
    colors[3] = vec3(0.0,1.0,1.0); //Cyan
    colors[4] = vec3(0.0,0.0,1.0); //Blue

    float height= 2;
    float slice = height/(NUM_COLORS-1);
    float vertex_height= (P.xyz).y +1;
    float height_in_slices = vertex_height/slice;
    int slice_lower = int(floor(height_in_slices));
    float gradient = fract(height_in_slices);
    vec3 grad_color = mix(colors[slice_lower],colors[slice_lower+1],gradient);


    frontColor =vec4(grad_color,1);

    gl_Position =modelViewProjectionMatrix * vec4(vertex, 1.0);
}
