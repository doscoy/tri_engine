
#if CROSS_GL_VERSION == CROSS_GL_ES2

const char* simple_vsh = R"(

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
)";

#else

const char* simple_vsh = R"(

#version 400
in vec4 a_position;
in vec3 a_normal;
out vec4 v_color;
uniform mat4 u_pmv;


void main(void)
{
    vec3 c = (a_normal + vec3(1, 1, 1)) / 2.0;
    
    v_color = vec4(c, 1.0);
    gl_Position = u_pmv * a_position;
}
)";



#endif

