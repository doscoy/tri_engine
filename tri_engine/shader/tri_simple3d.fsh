#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* simple3d_fsh = R"(


varying lowp vec2 v_texture_uv;
uniform sampler2D sampler;


void main(void)
{
    gl_FragColor = texture2D(sampler, v_texture_uv);
}


)";

#else
/*
//  GLSL4.0
const char* simple3d_fsh = R"(

#version 400
in vec2 v_texture_uv;
uniform sampler2D sampler;
out vec4 FragColor;

void main(void)
{
    FragColor = texture(sampler, v_texture_uv);
}


)";
*/

const char* simple3d_fsh = R"(
#version 400
uniform sampler2D sampler;
in vec2 v_texture_uv;
out vec4 FragColor;

void main(void) {
    vec4 dam = texture(sampler, v_texture_uv);
    FragColor = vec4(1,1,0,1);
}
)";
#endif