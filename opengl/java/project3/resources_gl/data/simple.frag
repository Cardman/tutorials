/*#if __VERSION__ >= 130
   #define varying in
   out vec4 mgl_FragColor;
   #define texture2D texture
 #else
   #define mgl_FragColor gl_FragColor  
#endif*/

uniform sampler2D mytex;

void main(void)
{
    //float fog = exp(-gl_Fog.density * gl_FogFragCoord) ;
    //fog = clamp(fog, 0.0,1.0);
    //vec3 couleur3 = mix(vec3(gl_Fog.color), gl_Color.rgb, fog);
	//gl_FragColor = vec4(couleur3,1.0);
	gl_FragColor = gl_Color;
	//gl_FragColor = texture2D(mytex,gl_TexCoord[0].st);
}
