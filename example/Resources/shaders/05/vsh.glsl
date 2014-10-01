#version 410 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec4 a_color;

out vec4 out_color;

void main(void)                                                   
{                                                                 
    gl_Position = a_position;
	out_color = a_color;
}                                                                 