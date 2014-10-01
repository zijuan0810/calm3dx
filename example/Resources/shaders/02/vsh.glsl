#version 430

layout (location = 0) in vec4 offset;
layout (location = 1) in vec4 color;

//varying out vec4 triangleClr;

// declare VS_OUT as an output interface block
out VS_OUT {
	vec4 color;
} vsOut;

void main()
{
	// declare a hard-code array of positions
	const vec4 vertices[3] = vec4[3](
		vec4( 0.25, -0.25, 0.5, 1.0), 
		vec4(-0.25, -0.25, 0.5, 1.0), 
		vec4( 0.25, 0.25, 0.5, 1.0));

	//triangleClr = color;
	vsOut.color = color;

	// index into our array using gl_VertexID
	gl_Position = vertices[gl_VertexID] + offset; 

	//gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
	//gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}