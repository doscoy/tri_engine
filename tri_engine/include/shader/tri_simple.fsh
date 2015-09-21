
#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0

const char* simple_fsh = R"(

varying lowp vec4 v_color;

void main(void)
{
    gl_FragColor = v_color;
}
)";

#elif CROSS_GL_VERSION == CROSS_GL_ES3

//  OpenGL ES 3.0
const char* simple_fsh = R"(
#version 300 es
precision mediump float;

in vec4 v_color;

void main(void)
{
    gl_FragColor = v_color;
}
)";



#else
//  GLSL 4.0

const char* simple_fsh = R"(
#version 400

in vec4 v_color;

void main(void)
{
    gl_FragColor = v_color;
}
)";




#endif

