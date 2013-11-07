#ifndef PLATFORM_MAC_HPP_INCLUDED
#define PLATFORM_MAC_HPP_INCLUDED

#include "platform_types.hpp"

namespace t3 {
class Color;
};
namespace glue {

void initializePlatform();
void prepareMainLoop();
void beginMainLoop();
void endMainLoop();


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
    return 1280;
}

// *********************************************
//  ウィンドウ高さ取得
constexpr inline int getScreenHeight(){
    return 720;
}


float oneFrameSec();

// *********************************************
//  クリアカラー設定
void setClearColor(
    const t3::Color& color
);   

// *********************************************
//  バッファスワップ
void swapBuffers();

// *********************************************
//  ディスプレイクリア
void clearDisplay( int flag );


bool isExitRequest();

}   // namespace glue




#endif // PLATFORM_MAC_HPP_INCLUDED
