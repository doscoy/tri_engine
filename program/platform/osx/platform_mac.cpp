#include "platform_types.hpp"
#include "platform_sdk.hpp"
#include "platform_mac.hpp"
#include "../../io/tri_pad.hpp"

#include "../../dbg/tri_dbg.hpp"
#include "../../kernel/tri_application.hpp"
#include "tri_game_system.hpp"
#include "fssimplewindow.h"



namespace glue {

namespace {
        
pad_data_t key_data_;
pointing_data_t mouse_data_;
        
}   // unname namespace

void initializePlatform()
{
    FsOpenWindow(40, 90, getScreenWidth(), getScreenHeight(), 1);
}


void prepareMainLoop()
{
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

}

void beginMainLoop()
{

    FsPollDevice();
    key_data_ = 0;
    int k = FsInkey();
    switch (k) {
        
        case FSKEY_Z:
            key_data_ |= t3::PAD_BUTTON_1;
            break;
        
        case FSKEY_X:
            key_data_ |= t3::PAD_BUTTON_2;
            break;
        
        case FSKEY_C:
            key_data_ |= t3::PAD_BUTTON_3;
            break;
        
        case FSKEY_LEFT:
            key_data_ |= t3::PAD_BUTTON_LEFT;
            break;
        
        case FSKEY_RIGHT:
            key_data_ |= t3::PAD_BUTTON_RIGHT;
            break;
            
        case FSKEY_UP:
            key_data_ |= t3::PAD_BUTTON_UP;
            break;
            
        case FSKEY_DOWN:
            key_data_ |= t3::PAD_BUTTON_DOWN;
            break;
            
        default:
            break;
    }
    
}

void endMainLoop()
{
    FsSleep(10);
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
    FsSwapBuffers();
}

void clearDisplay( int flag )
{
    glClear( flag );
}






}   // namespace glue

