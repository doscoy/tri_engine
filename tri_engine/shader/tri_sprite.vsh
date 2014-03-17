static const char* sprite_vsh = STRINGIFY(

attribute vec4 position;
attribute vec2 uv;

uniform mat4 projection;
uniform mat4 transform;

varying lowp vec2 texture_uv;

void main(void)
{
    gl_Position = projection * transform * position;
    texture_uv = uv;
}
);
