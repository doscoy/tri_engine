
#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
static const char* sprite_fsh = R"(

varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;
uniform sampler2D sampler;


void main(void)
{
    gl_FragColor = texture2D(sampler, v_texture_uv) * v_color;
}


)";

#else
//  GLSL 4.0
static const char* sprite_fsh = R"(

#version 400

in vec2 v_texture_uv;
in vec4 v_color;
out vec4 FragColor;
uniform sampler2D sampler;


void main(void)
{
    FragColor = texture(sampler, v_texture_uv) * v_color;
}


)";

#endif
