#version 410 core

in vec4 out_color;

out vec4 color;                      

void main(void)
{                                    
    //color = vec4(0.0, 0.8, 1.0, 1.0);
	color = out_color;
}