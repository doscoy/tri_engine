static const char* font_vsh = TRI_INSTANT_SHADER(

attribute vec2 in_position;
attribute vec2 in_uv;
attribute vec4 in_color;

varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;

void main(void)
{
    gl_Position = vec4(in_position, 0.0, 1.0);
    v_color = in_color;
    v_texture_uv = in_uv;
}
);
