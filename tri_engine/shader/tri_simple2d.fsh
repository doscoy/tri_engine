#ifndef SIMPLE_2D_FSH
#define SIMPLE_2D_FSH


const char* simple2d_fsh = TRI_INSTANT_SHADER(

varying lowp vec4 out_color;

void main(void)
{
    gl_FragColor = out_color;
}
);


#endif // SIMPLE_2D_FSH
