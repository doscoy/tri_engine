const char* simple3d_vsh = TRI_INSTANT_SHADER(

attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_uv;

varying lowp vec2 v_texture_uv;

uniform mat4 u_pmv;


void main(void)
{
    gl_Position = u_pmv * a_position;
    v_texture_uv = a_uv;

}
);
