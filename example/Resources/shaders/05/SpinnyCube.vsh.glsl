#version 410 core
#extension GL_ARB_explicit_uniform_location : enable

layout (location = 0) in vec4 position;

out VS_OUT
{                                                            
    vec4 color;                                              
} vs_out;

layout (location = 10) uniform mat4 mv_matrix;
layout (location = 11) uniform mat4 proj_matrix;

void main(void)
{ 
    gl_Position = proj_matrix * mv_matrix * position;
    vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}