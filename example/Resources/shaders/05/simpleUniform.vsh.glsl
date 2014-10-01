#version 410 core
#extension GL_ARB_explicit_uniform_location : enable

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec4 a_color;

uniform float fTime;
uniform int iIndex;
uniform vec4 vColorValue;
uniform mat4 mvpMatrix;

layout (location = 17) uniform vec4  myUniform;

layout(std140) uniform TransformBlock {
	float scale;
	vec3 translation;
	float rotation[3];
	mat4 projection_matrix;
} transform;

//out vec4 out_color;

void main(void)                                                   
{                                                                 
    gl_Position = a_position;
	//out_color = a_color;
}                                                                 