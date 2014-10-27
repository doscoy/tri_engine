static const char* font_fsh = TRI_INSTANT_SHADER(

varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;

uniform sampler2D sampler;

void main(void)
{
    lowp vec4 tex_color = texture2D(sampler, v_texture_uv);
    tex_color.rgb = v_color.rgb;
    gl_FragColor = tex_color;
}
);
