#ifndef SIMPLE_TEX_VSH
#define SIMPLE_TEX_VSH


constexpr char* simple_tex_vsh = TRI_INSTANT_SHADER(

attribute vec2 a_position;
attribute vec2 a_uv;
varying lowp vec2 v_texture_uv;

void main(void)
{
    gl_Position = vec4(a_position, 0, 1);
    v_texture_uv = a_uv;
}
);


#endif // SIMPLE_TEX_VSH