uniform sampler2D mytex;

void main(void)
{
    vec4 color_ = texture2D(mytex,gl_TexCoord[0].ts);
    vec4 realColor_ = vec4(color_.r,(color_.b+color_.g)/2.0,color_.a,color_.r);
    if (realColor_.rgb == vec3(1.0,1.0,1.0)) {
        discard;
        return;
    }
    //vec4 color_ = texture2D(mytex,gl_TexCoord[0].st);
    //gl_FragColor = vec4(color_.r,(color_.b+color_.r)/2.0,color_.b,color_.a);// color_.bgra;
    gl_FragColor = realColor_;// color_.bgra;
    //gl_FragColor = color_;
    //gl_FragColor = vec4(color_.r,color_.r,color_.r,color_.a);// color_.bgra;
    //gl_FragColor = texture2D(mytex,gl_TexCoord[0].st);
}