static const char* font_fsh = STRINGIFY(

varying lowp vec2 out_uv;
varying lowp vec4 out_color;

uniform sampler2D SAMPLER;

void main(void)
{
    gl_FragColor = texture2D(SAMPLER, out_uv) * out_color;
}
);
