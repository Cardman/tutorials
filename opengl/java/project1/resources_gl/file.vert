#if __VERSION__ >= 130
   #define attribute in
   #define varying out
#endif

uniform float mandel_x;
uniform float mandel_y;
uniform float mandel_width;
uniform float mandel_height;
uniform float mandel_iterations;

uniform vec3 mandel_couleur;

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
    //gl_FragColor = gl_Color;
    //gl_FragCoord = vec2(mandel_x, mandel_y)
    //gl_FragColor = vec4(1.0f,0.0f,1.0f,1.0f);
    //gl_FragColor = vec4(1.0f,1.0f,0.0f,1.0f);
    //gl_SecondaryColor = 1;
    //gl_Color = vec4(1.0f,0.0f,1.0f,1.0f);
    gl_FrontColor = vec4(mandel_couleur,255.0);
    //gl_FragColor = mandel_couleur;
}