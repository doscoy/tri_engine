#ifndef SIMPLE_TEX_FSH
#define SIMPLE_TEX_FSH


const char* simple_tex_fsh = TRI_INSTANT_SHADER(

varying lowp vec2 v_texture_uv;
uniform sampler2D sampler;


void main(void)
{
    gl_FragColor = vec4(texture2D(sampler, v_texture_uv).xyz, 1.0);
}


);




#endif // SIMPLE_2D_FSH
