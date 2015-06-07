#ifndef SIMPLE_2D_FSH
#define SIMPLE_2D_FSH

#if CROSS_GL_VERSION == CROSS_GL_ES2
//  Open GL ES 2.0
const char* simple2d_fsh = R"(

varying lowp vec4 out_color;

void main(void)
{
    gl_FragColor = out_color;
}
)";

#else

//  GLSL 4.0
const char* simple2d_fsh = R"(
#version 400
in vec4 out_color;
out vec4 FragColor;

void main(void)
{
    FragColor = out_color;
}
)";


#endif

#endif // SIMPLE_2D_FSH
