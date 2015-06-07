#ifndef SIMPLE_2D_VSH
#define SIMPLE_2D_VSH

#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* simple2d_vsh = R"(

attribute vec4 in_position;
uniform vec4 in_color;
varying lowp vec4 out_color;

void main(void)
{
    out_color = in_color;
    gl_Position = in_position;
}
)";

#else
//  GLSL 4.0
const char* simple2d_vsh = R"(
#version 400
in vec4 in_position;
uniform vec4 in_color;
out vec4 out_color;

void main(void)
{
    out_color = in_color;
    gl_Position = in_position;
}
)";


#endif

#endif // SIMPLE_2D_VSH