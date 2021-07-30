uniform sampler2D mytex;

void main(void)
{
    gl_FragColor = texture2D(mytex,gl_TexCoord[0].st);
}