
#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* simple3d_fsh = R"(


varying lowp vec2 v_texture_uv;
uniform sampler2D sampler;


void main() {
    gl_FragColor = texture2D(sampler, v_texture_uv);
}


)";

#elif CROSS_GL_VERSION == CROSS_GL_ES3

//  OpenGL ES 3.0
const char* simple3d_fsh = R"(

#version 300 es
precision mediump float;
in vec2 v_texture_uv;
uniform sampler2D sampler;
out vec4 FragColor;

void main() {
    FragColor = texture(sampler, v_texture_uv);
}
)";

#else

//  GLSL4.0
const char* simple3d_fsh = R"(

#version 400
in vec2 v_texture_uv;
uniform sampler2D sampler;
out vec4 FragColor;

void main() {
    FragColor = texture(sampler, v_texture_uv);
}
)";

#endif