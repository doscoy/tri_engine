static const char* sprite_fsh = STRINGIFY(

varying lowp vec2 texture_uv;

uniform sampler2D sampler;


void main(void)
{
    gl_FragColor = texture2D(sampler, texture_uv);
}
);
