const char* simple3d_fsh = TRI_INSTANT_SHADER(

varying lowp vec2 v_texture_uv;
uniform sampler2D sampler;


void main(void)
{
    gl_FragColor = texture2D(sampler, v_texture_uv);
}


);
