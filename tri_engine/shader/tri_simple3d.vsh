
#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* simple3d_vsh = R"(

attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_uv;

varying lowp vec2 v_texture_uv;

uniform mat4 u_pmv;


void main(void)
{
    vec3 nn = a_normal;
    gl_Position = u_pmv * a_position;
    v_texture_uv = a_uv;

}
)";

#else
//  GLSL 4.0
const char* simple3d_vsh = R"(

#version 400

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;
out float power;
out vec2 v_texture_uv;

uniform mat4 u_pmv;


void main(void)
{
    vec3 light_dir = vec3(1,0,0);
    gl_Position = u_pmv * a_position;
    v_texture_uv = a_uv;
    power = dot(a_normal, light_dir) * 0.5 + 0.5;

}
)";


#endif
