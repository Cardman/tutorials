/*#if __VERSION__ >= 130
   #define attribute in
   #define varying out
#endif

uniform vec3 couleur;// = vec3(255.0f,255.0f,255.0f);
attribute vec3 couleur2;

void main (void)
{
	gl_Position = ftransform();	
	gl_FrontColor = vec4(couleur[2],couleur[1],couleur[0],1.0);
	gl_FrontColor = vec4(couleur2,1.0);
}*/

attribute vec3 couleur;// = vec3(0.0f,1.0f,0.0f);

//uniform sampler2D mytex;
//attribute float couleur2;
//attribute float couleur3;
//attribute float couleur4;// = 0.0f;

void main (void)
{
    gl_Position = ftransform();
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = vec4(couleur.z,couleur.y,couleur.x,1.0);
    //gl_FrontColor = vec4(couleur,1.0);
}
