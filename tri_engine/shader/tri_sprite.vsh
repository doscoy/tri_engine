static const char* sprite_vsh = STRINGIFY(

attribute vec4 a_position;
attribute vec2 a_uv;
attribute vec4 a_color;

varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;


void main(void)
{
    gl_Position = a_position;
    v_texture_uv = a_uv;
    v_color = a_color;
}
);
