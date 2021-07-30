//uniform sampler2D mytex;

void main (void)
{
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    //gl_FrontColor = gl_Color.bgra;
    gl_Position = ftransform();
    //gl_FrontColor = vec4(couleur,1.0);
}
