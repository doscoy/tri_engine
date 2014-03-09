static const char* font_vsh = STRINGIFY(

attribute vec2 in_position;
attribute vec2 in_uv;
attribute vec4 in_color;

varying vec2 out_uv;
varying vec4 out_color;

void main(void)
{
    gl_Position = vec4(in_position, 0.0, 1.0);
    out_color = in_color;
    out_uv = in_uv;
}
);
