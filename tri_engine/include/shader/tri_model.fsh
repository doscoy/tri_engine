
#if CROSS_GL_VERSION == CROSS_GL_ES2
//  OpenGL ES 2.0
const char* model_fsh = R"(


varying lowp vec2 v_texture_uv;
varying lowp vec4 v_shadow_coord;

uniform sampler2D sampler;
uniform sampler2DShadow shadow_samp;
uniform bool draw_flag;
uniform bool draw_shadow;


void main() {
//    if (draw_flag) {
//        lowp vec4 tex_color = texture2D(sampler, v_texture_uv);
//        if (draw_shadow) {
//            float shadow = texture2DProj(shadow_samp, v_shadow_coord.xyz) * 0.5 + 0.5;
//            gl_FragColor = vec4(tex_color.xyz * shadow, 1.0);
//        } else {
//           gl_FragColor = tex_color;
//        }
//    }
    gl_FragColor = texture2D(sampler, v_texture_uv);
}


)";


#elif CROSS_GL_VERSION == CROSS_GL_ES3

//  OpenGL ES 3.0
const char* model_fsh = R"(

#version 300 es
precision mediump float;

in vec2 v_texture_uv;
in vec4 v_shadow_coord;

uniform sampler2D sampler;
uniform mediump sampler2DShadow shadow_samp;
uniform bool draw_flag;
uniform bool draw_shadow;
out vec4 FragColor;

void main() {
    if (draw_flag) {
        vec4 tex_color = texture(sampler, v_texture_uv);
        if (draw_shadow) {
            float shadow = textureProj(shadow_samp, v_shadow_coord) * 0.5 + 0.5;
            FragColor = vec4(tex_color.xyz * shadow, 1.0);
        } else {
            FragColor = tex_color;
        }
    }
}


)";


#else

//  GLSL4.0
const char* model_fsh = R"(

#version 400

in vec2 v_texture_uv;
in vec4 v_shadow_coord;

uniform sampler2D sampler;
uniform sampler2DShadow shadow_samp;
uniform bool draw_flag;
uniform bool draw_shadow;
out vec4 FragColor;

void main() {
    if (draw_flag) {
        vec4 tex_color = texture(sampler, v_texture_uv);
        if (draw_shadow) {
            float shadow = textureProj(shadow_samp, v_shadow_coord) * 0.5 + 0.5;
            FragColor = vec4(tex_color.xyz * shadow, 1.0);
        } else {
            FragColor = tex_color;
        }
    }
}


)";

#endif