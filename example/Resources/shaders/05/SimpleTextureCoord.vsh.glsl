#version 430

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

out VS_OUT {
	vec2 tc;
} vs_out;

void main()
{
	// Calculate the position of each vertex
	vec4 pos_vs = mv_matrix * position;

	// Pass the texture coordinate through unmodified
	vs_out.tc = texCoord;

	gl_Position = proj_matrix * pos_vs;
}