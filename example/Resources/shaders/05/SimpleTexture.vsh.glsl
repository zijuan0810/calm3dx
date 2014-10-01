#version 410 core
#extension GL_ARB_explicit_uniform_location : enable

//layout (location = 0) in vec4 position;
//layout (location = 10) uniform mat4 mv_matrix;
//layout (location = 11) uniform mat4 proj_matrix;

void main(void)
{ 
	const vec4 vertices[] = vec4[](
		vec4( 0.75, -0.75, 0.5, 1.0), 
		vec4(-0.75, -0.75, 0.5, 1.0), 
		vec4( 0.75,  0.75, 0.5, 1.0));

	gl_Position = vertices[gl_VertexID];
    //gl_Position = proj_matrix * mv_matrix * position;
    //vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}