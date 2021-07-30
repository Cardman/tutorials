uniform sampler2D mytex;

varying vec4 valls;

void main(void)
{
    vec4 color_ = texture2D(mytex,gl_TexCoord[0].st);
    float mid_ = (color_.r+color_.g+color_.b)/3.0;
    vec4 realColor_ = vec4(mid_*valls.g,mid_*valls.r,mid_*valls.b,color_.a);
    /*if (realColor_.rgb == vec3(1.0,1.0,1.0)) {
        discard;
    }*/
    if (realColor_.g >= 0.7) {
        discard;
    }
    gl_FragColor = realColor_;
    //gl_FragColor = vec4(color_.r*valls.b,color_.g*valls.g,color_.b*valls.r,color_.a);
}