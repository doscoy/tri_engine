#include "platform_types.hpp"
#include "platform_sdk.hpp"
#include "platform_mac.hpp"
#include "../../io/tri_pad.hpp"

#include "../../dbg/tri_dbg.hpp"
#include "../../kernel/tri_application.hpp"
#include "tri_game_system.hpp"
#include "fssimplewindow.h"
#include "cocoa_keycode.h"


namespace glue {

namespace {
        
pad_data_t key_data_;
pointing_data_t mouse_data_;
float tick_;

}   // unname namespace

void initializePlatform()
{
    FsOpenWindow(40, 90, getScreenWidth(), getScreenHeight());
}


void prepareMainLoop()
{
    tick_ = 0.0166f;

}

void beginMainLoop()
{

    FsPollDevice();
    key_data_ = 0;
 
    if(FsIsKey(FSKEY_Z)){
        key_data_ |= t3::Pad::BUTTON_1;
    }
    if(FsIsKey(FSKEY_X)){
        key_data_ |= t3::Pad::BUTTON_2;
    }
    if(FsIsKey(FSKEY_C)){
        key_data_ |= t3::Pad::BUTTON_3;
    }
    if(FsIsKey(FSKEY_RIGHT)){
        key_data_ |= t3::Pad::BUTTON_RIGHT;
    }
    if(FsIsKey(FSKEY_LEFT)){
        key_data_ |= t3::Pad::BUTTON_LEFT;
    }
    if(FsIsKey(FSKEY_UP)){
        key_data_ |= t3::Pad::BUTTON_UP;
    }
    if(FsIsKey(FSKEY_DOWN)){
        key_data_ |= t3::Pad::BUTTON_DOWN;
    }
}

void endMainLoop()
{
    float ms = FsPassedTime();
    FsSleep(16.0f - ms);
    tick_ = ms * 0.001f;
}

float oneFrameSec()
{
    return tick_;
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

