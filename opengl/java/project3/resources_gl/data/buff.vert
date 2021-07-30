attribute vec3 inputPosition;
attribute vec4 inputColor;

varying vec3 forFragColor;

void main() 
{
  forFragColor = inputColor.rgb;
  gl_Position = vec4(inputPosition, 1.0);
}