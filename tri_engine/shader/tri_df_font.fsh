#if CROSS_GL_VERSION == CROSS_GL_ES2
const char* df_font_fsh = TRI_INSTANT_SHADER(


varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;

uniform sampler2D sampler;
const mediump float SmoothCenter = 0.5;
const mediump float SmoothWidth = 0.1;

void main()
{
    mediump vec4 color = texture2D(sampler, v_texture_uv);
    mediump float alpha = smoothstep(0.3, 0.99, color.a);
    gl_FragColor = vec4(color.rgb, alpha);
}
);

#else

static const char* df_font_fsh = "#extension GL_OES_standard_derivatives : enable\n" TRI_INSTANT_SHADER(

varying lowp vec2 v_texture_uv;
varying lowp vec4 v_color;

uniform sampler2D sampler;
const mediump float SmoothCenter = 0.9;

void main()
{
    mediump vec4 color = texture2D(sampler, v_texture_uv);
    mediump float SmoothWidth = fwidth(color.a);
    mediump float alpha = smoothstep(SmoothCenter - SmoothWidth, SmoothCenter + SmoothWidth, color.a);
    gl_FragColor = vec4(v_color.rgb, alpha);
}
);


#endif