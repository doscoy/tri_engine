
#if CROSS_GL_VERSION == CROSS_GL_ES2
constexpr char* simple_tex_vsh = R"(

attribute vec2 a_position;
attribute vec2 a_uv;
varying lowp vec2 v_texture_uv;

void main(void)
{
    gl_Position = vec4(a_position, 0, 1);
    v_texture_uv = a_uv;
}
)";

#elif CROSS_GL_VERSION == CROSS_GL_ES3

//  OpenGL ES 3.0
constexpr char* simple_tex_vsh = R"(

#version 300 es
precision mediump float;

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_uv;
out vec2 v_texture_uv;

void main(void)
{
    gl_Position = vec4(a_position, 0, 1);
    v_texture_uv = a_uv;
}
)";


#else
//  GLSL 4.0
constexpr char* simple_tex_vsh = R"(

#version 400

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_uv;
out vec2 v_texture_uv;

void main(void)
{
    gl_Position = vec4(a_position, 0, 1);
    v_texture_uv = a_uv;
}
)";


#endif


