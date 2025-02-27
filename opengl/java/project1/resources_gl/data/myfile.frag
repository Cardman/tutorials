/* Very simple fragment shader. It basically passes the
 * (interpolated) vertex color on to the individual pixels.
 */ 
#version 400
 
// corresponds with output from vertex shader
in vec3 Color;
 
out vec4 FragColor;
 
void main()
{
    // assign vertex color to pixel color
    FragColor = vec4(Color, 1.0);
}