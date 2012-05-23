#ifndef PLATFORM_MAC_HPP_INCLUDED
#define PLATFORM_MAC_HPP_INCLUDED

#include "platform_types.hpp"

namespace t3 {
class Application;
};
namespace glue {

void applicationExecuter( t3::Application& app );


// *********************************************
//  パッドデータ取得
pad_data_t getPlatformPadData( int pad_no );
pad_data_t getPlatformDebugPadData();


// *********************************************
//  ポインティングデータ取得
const pointing_data_t& getPlatformPointingData();

// *********************************************
//  ウィンドウ幅取得
constexpr inline int getScreenWidth(){
    return 640;
}

// *********************************************
//  ウィンドウ高さ取得
constexpr inline int getScreenHeight(){
    return 480;
}


// *********************************************
//  ウィンドウ高さ取得
void setClearColor(
    float r,
    float g,
    float b
);   

// *********************************************
//  ウィンドウ高さ取得
void swapBuffers();

// *********************************************
//  ウィンドウ高さ取得    
void clearDisplay( int flag );

}   // namespace glue




#endif // PLATFORM_MAC_HPP_INCLUDED
