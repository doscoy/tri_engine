#ifndef SIMPLE_2D_VSH
#define SIMPLE_2D_VSH


const char* simple2d_vsh = TRI_INSTANT_SHADER(

attribute vec4 in_position;
uniform vec4 in_color;
varying lowp vec4 out_color;

void main(void)
{
    out_color = in_color;
    gl_Position = in_position;
}
);


#endif // SIMPLE_2D_VSH