#include "platform_types.hpp"
#include "platform_sdk.hpp"
#include "platform.hpp"
#include "../io/tri_pad.hpp"

#include "../dbg/tri_dbg.hpp"
#include "../kernel/tri_application.hpp"
#include "tri_game_system.hpp"


namespace {

t3::Application* app_;
glue::pad_data_t key_data_;
glue::pointing_data_t mouse_data_;

void special_key(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_RIGHT:
            key_data_ |= t3::PAD_BUTTON_RIGHT;
            break;
            
        case GLUT_KEY_LEFT:
            key_data_ |= t3::PAD_BUTTON_LEFT;
            break;
        
        case GLUT_KEY_UP:
            key_data_ |= t3::PAD_BUTTON_UP;
            break;
            
        case GLUT_KEY_DOWN:
            key_data_ |= t3::PAD_BUTTON_DOWN;
            break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'z':
        case 'Z':
            key_data_ |= t3::PAD_BUTTON_1;
            break;

        case 'x':
        case 'X':
            key_data_ |= t3::PAD_BUTTON_2;
            break;
        
        case 'c':
        case 'C':
            key_data_ |= t3::PAD_BUTTON_3;
            break;
            
        default:
            break;
    }
}

void display()
{
}

void timer( int value ) {

    glutTimerFunc(18 , timer , 0);
	glutPostRedisplay();
    app_->update(0.0166f);
    key_data_ = 0;
    //glFlush();
}



void on_mouse( int x, int y )
{
    mouse_data_.x = x;
    mouse_data_.y = y;
    mouse_data_.hit = true;
}
void off_mouse( int x, int y )
{
    mouse_data_.x = x;
    mouse_data_.y = y;
    mouse_data_.hit = false;
}

}   // unname namespace


namespace glue {


void applicationExecuter( t3::Application& app )
{
    int argc = 0;
    char* argv[] = {0,0};
    
    app_ = &app;
    
    
    
    glutInitWindowSize( getScreenWidth(), getScreenHeight() );
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
//    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(off_mouse);
    glutMotionFunc(on_mouse);
    glutSpecialFunc(special_key);
    
    
    glEnable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );

    glutTimerFunc( 32, timer, 0);
    app.initializeApplication();
    

    glutMainLoop();
    

}

pad_data_t getPlatformPadData( int pad_no )
{
    if ( pad_no >= 1 ){
        return 0;
    }
    
    pad_data_t b = key_data_;
    return b;
}

pad_data_t getPlatformDebugPadData()
{
    return getPlatformPadData( 0 );
}

void setClearColor(
    const t3::Color& color
){
    glClearColor(
        color.redf(),
        color.greenf(),
        color.bluef(),
        color.alphaf()
    );
}

void swapBuffers()
{
    glutSwapBuffers();
}

void clearDisplay( int flag )
{
    glClear( flag );
}






}   // namespace glue

