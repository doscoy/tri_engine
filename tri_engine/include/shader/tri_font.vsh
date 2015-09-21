
#if CROSS_GL_VERSION == CROSS_GL_ES2
// OpenGL ES 2.0
static const char* font_vsh = R"(

attribute vec2 in_position;
attribute vec2 in_uv;
attribute vec4 in_color;

varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;

void main(void)
{
    gl_Position = vec4(in_position, 0.0, 1.0);
    v_color = in_color;
    v_texture_uv = in_uv;
}
)";

#elif CROSS_GL_VERSION == CROSS_GL_ES3

//  OpenGL ES 3.0
static const char* font_vsh = R"(
#version 300 es
precision mediump float;
in vec2 in_position;
in vec2 in_uv;
in vec4 in_color;

out vec2 v_texture_uv;
out vec4 v_color;

void main(void)
{
    gl_Position = vec4(in_position, 0.0, 1.0);
    v_color = in_color;
    v_texture_uv = in_uv;
}
)";


#else

//  GLSL 4.0
static const char* font_vsh = R"(
#version 400
in vec2 in_position;
in vec2 in_uv;
in vec4 in_color;

out vec2 v_texture_uv;
out vec4 v_color;

void main(void)
{
    gl_Position = vec4(in_position, 0.0, 1.0);
    v_color = in_color;
    v_texture_uv = in_uv;
}
)";

#endif
