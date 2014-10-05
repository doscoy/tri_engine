static const char* sprite_fsh = TRI_INSTANT_SHADER(



varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;
uniform sampler2D sampler;


void main(void)
{
    gl_FragColor = texture2D(sampler, v_texture_uv) * v_color;
}











);
