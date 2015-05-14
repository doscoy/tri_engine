/**
    @file cross_os.hpp
    入力情報等の低級API.
*/

#ifndef CROSS_BASE_HPP_INCLUDED
#define CROSS_BASE_HPP_INCLUDED


//  include
#include "cross_types.hpp"

///
/// cross_sdkのトップレベルネームスペース.
namespace cross {


///
/// プラットフォーム初期化
void initializePlatform(
    int w,
    int h,
    const char* title
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
    const char* const str
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







}   // namespace cross

#endif // PLATFORM_HPP_INCLUDED
