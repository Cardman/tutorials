precision mediump float; 
varying vec3 forFragColor;
//varying vec3 baboin;

void main() 
{
  gl_FragColor = vec4(forFragColor,1.0);
  //gl_FragColor = vec4(baboin,1.0);
}