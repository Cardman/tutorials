
uniform sampler2D mytex;
attribute vec3 mycolor;

void main (void)
{
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0.yxzw;
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = vec4(mycolor.bgr,1);
    gl_Position = ftransform();
    //gl_FrontColor = gl_Color.bgra;
    //gl_FrontColor = vec4(couleur,1.0);
}
