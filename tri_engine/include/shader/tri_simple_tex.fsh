#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* simple_tex_fsh = R"(

varying lowp vec2 v_texture_uv;
uniform sampler2D sampler;


void main(void)
{
    gl_FragColor = vec4(texture2D(sampler, v_texture_uv).xyz, 1.0);
}

)";

#else
// GLSL 4.0
const char* simple_tex_fsh = R"(

#version 400

in vec2 v_texture_uv;
uniform sampler2D sampler;
layout (location = 0) out vec4 FragColor;

void main(void)
{
    FragColor = texture(sampler, v_texture_uv);
}

)";

#endif