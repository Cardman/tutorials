#if __VERSION__ >= 130
   #define varying in
   out vec4 mgl_FragColor;
   #define texture2D texture
 #else
   #define mgl_FragColor gl_FragColor  
#endif


uniform float mandel_x;
uniform float mandel_y;
uniform float mandel_width;
uniform float mandel_height;
uniform float mandel_iterations;
uniform vec3 mandel_couleur;

float calculateMandelbrotIterations(float x, float y) {
    float xx = 0.0;
    float yy = 0.0;
    float iter = 0.0;
    float nbiter = mandel_iterations * 2;
    while (xx * xx + yy * yy <= 4.0 && iter<nbiter) {
        float temp = xx*xx - yy*yy + x;
        yy = 2.0*xx*yy + y;

        xx = temp;

        iter ++;
    }
    return iter;
}

vec4 getColor(float iterations) {
    float oneThirdMandelIterations = mandel_iterations/3.0;
    float green = iterations/oneThirdMandelIterations;
    float blue = (iterations-1.3*oneThirdMandelIterations)/oneThirdMandelIterations;
    float red = (iterations-2.2*oneThirdMandelIterations)/oneThirdMandelIterations;
    return vec4(red,green,blue,1.0);
}

void main() {
    float x = mandel_x+gl_TexCoord[0].x*mandel_width;
    float y = mandel_y+gl_TexCoord[0].y*mandel_height;
    float iterations = calculateMandelbrotIterations(x,y);
    //gl_Color = vec4(mandel_couleur, 1.0);
    gl_FragColor = getColor(iterations);
    //gl_FragColor = vec4(1.0f,1.0f,0.0f,1.0f);
    //gl_Color = vec4(1.0f,0.0f,1.0f,1.0f);
}