#version 410 core
                         
out vec4 color;          

uniform sampler2D s2d;                         
                       
void main(void)          
{                        
	//color = texture(s2d, gl_FragCoord.xy / textureSize(s2d, 0));
	color = texelFetch(s2d, ivec2(gl_FragCoord.xy), 0);
}                        