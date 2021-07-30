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

attribute vec3 couleur2;// = vec3(0.0f,1.0f,0.0f);
/*layout(location = 1) out int materialID;
layout(location = 4) out vec3 normal;
layout(location = 0) out vec4 diffuseColor;
layout(location = 3) out vec3 position;
layout(location = 2) out vec4 specularColor;*/
//attribute float couleur2;
//attribute float couleur3;
//attribute float couleur4;// = 0.0f;

void main (void)
{
    gl_Position = ftransform();
//    float fog = exp(-gl_Fog.density * gl_FogFragCoord) ;
    float fog = (gl_Fog.end - gl_FogFragCoord) /gl_Fog.scale;
    fog = clamp(fog, 0.0,1.0);
    vec3 couleur3 = mix(vec3(gl_Fog.color), couleur2, fog);
    //couleur3 = couleur2;
    gl_FrontColor = vec4(couleur3, 1.0);
    //gl_FrontColor = vec4(couleur,1.0);
}
