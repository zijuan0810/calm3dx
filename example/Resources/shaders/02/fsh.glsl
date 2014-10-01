#version 430

out vec4 color;

// declare VS_OUT as an input interface block
in VS_OUT {
	vec4 color;
} vsIn;


void main()
{
	//color = vec4(0.0, 0.8, 1.0, 1.0);
	color = vsIn.color;
}