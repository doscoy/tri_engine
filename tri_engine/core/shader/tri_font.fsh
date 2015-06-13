#if CROSS_GL_VERSION == CROSS_GL_ES2
// Open GL ES 2.0
static const char* font_fsh = R"(

varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;

uniform sampler2D sampler;

void main(void)
{
    lowp vec4 tex_color = texture2D(sampler, v_texture_uv);
    gl_FragColor = vec4(v_color.rgb, v_color.a * tex_color.a);
}
)";


#else

//  GLSL 4.0
static const char* font_fsh = R"(

#version 400

in vec2 v_texture_uv;
in vec4 v_color;
out vec4 FragColor;

uniform sampler2D sampler;

void main(void)
{
    vec4 tex_color = texture(sampler, v_texture_uv);
    FragColor = vec4(v_color.rgb, v_color.a * tex_color.a);
}
)";



#endif