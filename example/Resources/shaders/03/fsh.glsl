#version 410 core
                                     
out vec4 color;                      
                                     
void main(void)                      
{                                    
    //color = vec4(0.0, 0.8, 1.0, 1.0);
    color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5, 
    			 cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5, 
    			 sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15), 
    			 1.0);
}                                    