static const char* sprite_fsh = STRINGIFY(



varying lowp vec4 a_color;
varying lowp vec2 v_texture_uv;
uniform sampler2D sampler;


void main(void)
{
    lowp vec4 color = texture2D(sampler, v_texture_uv) * a_color;
    gl_FragColor = color;
}











);
