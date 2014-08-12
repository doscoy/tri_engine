const char* SimpleVertexShader = STRINGIFY(

attribute vec4 a_position;
varying lowp vec4 v_color;
uniform mat4 u_pmv;


void main(void)
{
    float b = clamp((a_position.y + 0.5), 0.0, 1.0);
    
    v_color = vec4(0.2, 0.2, b, 1.0);
    gl_Position = u_pmv * a_position;
}
);
