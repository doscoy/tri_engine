
#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* model_fsh = R"(


varying lowp vec2 v_texture_uv;
uniform sampler2D sampler;


void main() {
    gl_FragColor = texture2D(sampler, v_texture_uv);
}


)";

#else

//  GLSL4.0
const char* model_fsh = R"(

#version 400

in vec4 v_shadow_coord;
in vec2 v_texture_uv;

uniform sampler2D sampler;
uniform sampler2DShadow shadow_samp;
out vec4 FragColor;

void main() {
    vec4 tex_color = texture(sampler, v_texture_uv);
    float shadow = textureProj(shadow_samp, v_shadow_coord);
    vec4 color = vec4(tex_color.xyz * shadow, 1.0);
    if (shadow > 0.99f) {
        color = vec4(1,0,0,1);
    }
    FragColor = color;
}


)";

#endif