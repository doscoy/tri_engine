const char* simple_fsh = TRI_INSTANT_SHADER(

varying lowp vec4 v_color;

void main(void)
{
    gl_FragColor = v_color;
}
);
