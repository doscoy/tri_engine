
#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* model_vsh = R"(

attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_uv;

varying lowp vec2 v_texture_uv;

uniform mat4 u_mvp;


void main() {
    vec3 nn = a_normal;
    gl_Position = u_mvp * a_position;
    v_texture_uv = a_uv;

}
)";

#else
//  GLSL 4.0
const char* model_vsh = R"(

#version 400

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec2 v_texture_uv;
out vec4 v_shadow_coord;


uniform mat4 u_mvp;
uniform mat4 u_shadow_mtx;

void main() {

    v_shadow_coord = u_shadow_mtx * vec4(a_position, 1.0);
    v_texture_uv = a_uv;

    gl_Position = u_mvp * vec4(a_position, 1.0);
}
)";


#endif
