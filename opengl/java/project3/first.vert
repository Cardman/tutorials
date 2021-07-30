#version 140
 
in vec3 inputPosition;
in vec4 inputColor;
 
out vec3 forFragColor;
 
void main(){
    forFragColor = inputColor.rgb;
    gl_Position =  vec4(inputPosition, 1.0);
}
