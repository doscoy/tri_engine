////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross_os.hpp
    入力情報等の低級API.
*/

#ifndef CROSS_BASE_HPP_INCLUDED
#define CROSS_BASE_HPP_INCLUDED


//  include
#include "cross_config.hpp"
#include "cross_types.hpp"

///
/// cross_sdkのトップレベルネームスペース.
CROSS_NS_BEGIN

///
/// 初期化用設定
class InitConfiguration {
public:
    int window_width_ = 100;
    int window_height_ = 100;
    int virtual_screen_width_ = 100;
    int virtual_screen_height_ = 100;
    bool full_screen_ = false;
    bool window_resizable_ = false;
    const char* title_ = "TriENGINE Application";
};


///
/// プラットフォーム初期化
bool initializePlatform(
    const InitConfiguration& config
);

///
/// プラットフォーム後片付け
void terminatePlatform();

///
/// アップデート前処理
void beginUpdate();

///
/// アップデート後処理
void endUpdate();

///
/// 描画後処理
void endRender();

///
/// パッドデータ取得
void platformPadData(
    int no,
    GamePadData* data
);

///
/// ポインティングデータ取得
void platformPointingData(
    int no,
    PointingData* data
);

///
/// 終了リクエスト判定
bool isExitRequest();

///
/// デバッグプリント
void printConsole(
    const char* str
);

///
/// デバイスの基本ファイルパスを取得
std::string getDeviceFilePath();

///
/// ファイル読み込み
void loadFile(
    const char* const file_path,
    uint8_t** data,
    size_t* size
);

///
/// 数値を保存
void saveInteger(
    const char* const label,    ///< 保存用ラベル
    int val                     ///< セーブする値
);

///
/// 数値を読み込み
void loadInteger(
    const char* const label,    ///< 保存用ラベル
    int* key                    ///< ロードする値
);



enum {
    PAD_BUTTON_A       = 0b0000000000000001,
    PAD_BUTTON_B       = 0b0000000000000010,
    PAD_BUTTON_X       = 0b0000000000000100,
    PAD_BUTTON_Y       = 0b0000000000001000,
    PAD_BUTTON_L       = 0b0000000000010000,
    PAD_BUTTON_R       = 0b0000000000100000,
    PAD_BUTTON_UP      = 0b0000000001000000,
    PAD_BUTTON_DOWN    = 0b0000000010000000,
    PAD_BUTTON_RIGHT   = 0b0000000100000000,
    PAD_BUTTON_LEFT    = 0b0000001000000000,
    PAD_BUTTON_OPTION1 = 0b0000010000000000,
    PAD_BUTTON_OPTION2 = 0b0000100000000000,
    PAD_BUTTON_HOME    = 0b0001000000000000,
    PAD_BUTTON_DEBUG1  = 0b0010000000000000,
    PAD_BUTTON_DEBUG2  = 0b0100000000000000,
    PAD_BUTTON_DEBUG3  = 0b1000000000000000,
};



CROSS_NS_END

#endif // PLATFORM_HPP_INCLUDED
