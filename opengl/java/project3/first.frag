#version 140
 
in vec3 forFragColor;
//in vec3 baboin;
out vec4 outputColor;
 
void main() {
    outputColor = vec4(forFragColor,1.0);
    //outputColor = vec4(baboin,1.0);
}
