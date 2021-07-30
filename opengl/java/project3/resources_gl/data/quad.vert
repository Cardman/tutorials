//uniform sampler2D mytex;

varying vec4 valls;

void main (void)
{
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_Position = ftransform();
    //valls = gl_Color.bgra;
    valls = vec4(1.0,0.3,0.3,0.3);
    //gl_FrontColor = gl_Color.bgra;
    //gl_FrontColor = vec4(couleur,1.0);
}
