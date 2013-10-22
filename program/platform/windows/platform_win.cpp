#include "platform_types.hpp"
#include "platform_sdk.hpp"
#include "platform_win.hpp"
#include "../../io/tri_pad.hpp"

#include "../../dbg/tri_dbg.hpp"
#include "../../kernel/tri_application.hpp"


namespace glue {

namespace {
        
pad_data_t key_data_;
pointing_data_t mouse_data_;
float tick_;

}   // unname namespace

void initializePlatform()
{

}


void prepareMainLoop()
{
    tick_ = 0.0166f;
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

}

void beginMainLoop()
{

}

void endMainLoop()
{

}

float oneFrameSec()
{

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

