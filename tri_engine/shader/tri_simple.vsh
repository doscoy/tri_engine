const char* simple_vsh = TRI_INSTANT_SHADER(

attribute vec4 a_position;
attribute vec3 a_normal;
varying lowp vec4 v_color;
uniform mat4 u_pmv;


void main(void)
{
    vec3 c = (a_normal + vec3(1, 1, 1)) / 2.0;
    
    v_color = vec4(c, 1.0);
    gl_Position = u_pmv * a_position;
}
);
