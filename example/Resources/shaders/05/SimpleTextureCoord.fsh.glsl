#version 430

layout (binding = 0) uniform sampler2D tex_object;

in VS_OUT {
	vec2 tc;
} vs_in;

out vec4 color;

void main()
{
	// Simply read from the texture at the (scaled) coordinates,
	// and assign the result to the shader's output
	color = texture(tex_object, vs_in.tc * vec2(3.0, 1.0));
}