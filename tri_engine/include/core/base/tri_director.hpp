////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_director.hpp
    ゲームシステム管理.
*/

#ifndef TRI_GAME_SYSTEM_HPP_INCLUDED
#define TRI_GAME_SYSTEM_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_event_manager.hpp"
#include "core/debug/tri_debugmenu.hpp"
#include "core/debug/tri_debug_string_layer.hpp"
#include "core/debug/tri_debug_log_layer.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/utility/random/tri_random.hpp"
#include "core/utility/tri_singleton.hpp"
#include "core/graphics/tri_color.hpp"
#include "core/graphics/tri_layer_base.hpp"
#include "core/graphics/tri_fade_layer.hpp"
#include "core/graphics/tri_sprite_layer.hpp"
#include "core/graphics/tri_surface.hpp"
#include "core/graphics/tri_cinema_layer.hpp"
#include "core/base/tri_task.hpp"


#include <array>



TRI_CORE_NS_BEGIN

constexpr int MAX_PAD = 4;  ///< パッド数

///
/// ディレクター
class Director 
    : public Singleton<Director>
{
    //  friend
    friend class Singleton<Director>;

public:
    //  乱数生成器のエイリアス
    using random_t = RandomNumberGenerator<RandomWell>;
    

private:
    ///
    /// デストラクタ
    Director();

    ///
    /// コンストラクタ
    ~Director();

public:
    ///
    /// ディレクターの初期化
    void initializeDirector();

    ///
    /// ディレクターの後片付け
    void terminateDirector();
    
    ///
    /// 最終レイヤーのセットアップ
    void setupFinalLayer();
    
    
    TaskPtr rootTask() {
        return root_task_;
    }
    
// ---------------------------------------------
//  乱数管理    
    
    ///
    /// 乱数ジェネレータ取得
    random_t& random(){
        return random_number_generator_;
    }
    

    ///
    /// ディレクターの更新
    void update(
        const DeltaTime delta_time
    );
  
    
    ///
    /// ディレクターの描画
    void render();
    
    
    
    ///
    /// 入力更新
    void updateInput(
        const DeltaTime delta_time
    );
    
    
    ///
    /// デバッグメニュー登録
    void registryToDebugMenu(
        DebugMenuFrame& parent_frame
    );
    

    ///
    /// 登録済レイヤー取得
    Layers& layers() {
        return layers_;
    }
    
    ///
    /// 登録済みレイヤー取得
    const Layers& layers() const {
        return layers_;
    }
    
    ///
    /// 終了リクエスト判定
    bool isExitRequest() const {
        return exit_request_;
    }

    ///
    /// レイヤー登録
    void attachLayer(LayerBase* layer);
    
    ///
    /// レイヤー削除
    void detachLayer(LayerBase* layer);
    

    ///
    /// 登録済みレイヤーのソート
    void sortLayers();
    
    ///
    /// ゲームスピード取得
    float getGameSpeed() const {
        return game_speed_;
    }
    
    
    ///
    /// タスク表示
    void showTask() const;
    

    ///
    /// クリアカラー取得
    const Color& getClearColor();

    ///
    /// クリアカラー設定
    void setClearColor(const Color& c);

    ///
    /// 入力情報を取得
    const Input& input(const int player_no = 0);
    
    ///
    /// 登録されている指定レイヤーを探す
    LayerBase* findLayer(const String& layer_name);
    
    
    ///
    /// ブラックアウト設定
    void setupBlackOut();

    ///
    /// ブラックイン設定
    void setupBlackIn();
    
    ///
    /// フェードアウト
    void fadeOut();
    
    ///
    /// フェードイン
    void fadeIn();
    
    ///
    /// フェード終了判定
    bool isFadeEnd();
    
    ///
    /// フェードイン終了判定
    bool isFadeInEnd();
    
    ///
    /// フェードアウト終了判定
    bool isFadeOutEnd();
    
    
    ///
    /// 画面にデバッグ文字を描画
    void printDisplay(
        const float x,
        const float y,
        const uint32_t color,
        const int font_size,
        const char* const str
    );
    
    ///
    /// 画面にログ出力
    void logDisplay(
        const char* const str
    );
    
    ///
    /// 最終レンダーターゲット取得
    auto& finalSurface() {
        return final_surface_;
    }
    
    ///
    /// デバイス向けレンダーターゲット取得
    auto& deviceSurface() {
        return device_surface_;
    }
    
    
    
private:
    

    ///
    /// デバッグメニューに登録
    void registryLayersToDebugMenu();

    ///
    /// デバッグメニューから削除
    void unregistryLayersToDebugMenu();

    ///
    /// デバッグプリントの更新前準備
    void prepareDebugPrintFontSprites();


    
private:
    //  デバッグ用レイヤー
    UniquePtr<DebugStringLayer> dbg_string_layer_;
    UniquePtr<DebugLogLayer> dbg_log_layer_;

    //  システムフェード
    UniquePtr<FadeLayer> fade_layer_;   ///< フェードレイヤー
    
    //  乱数
    random_t random_number_generator_;  ///< 乱数生成器

    //  インプットデータ
    Array<Input, MAX_PAD> input_;       ///< 入力データ

    //  描画レイヤー
    Layers layers_;                     ///<  描画レイヤー
    
    //  デバイスのレンダーターゲット
    UniquePtr<DeviceSurface> device_surface_;
    
    //  最終レンダーターゲット
    UniquePtr<FrameBufferSurface> final_surface_;
    
    //  最終レンダーターゲット描画レイヤ
    UniquePtr<CinemaLayer> final_layer_;
    
    
    //  ルートタスク
    //  全タスクはここにぶら下がる形になる
    TaskPtr root_task_;
    
    
    //  クリアカラー
    DebugMenuItem<int> dm_color_idx_;   ///< スクリーンクリアカラー
    int use_clear_color_index_;         ///< 使用するスクリーンクリアカラー番号
    Array<Color, 4> clear_colors_;      ///< スクリーンクリアカラーの定義
    
    //  エージング用ランダムタッチ
    DebugMenuItem<bool> dm_random_pointing_;    ///< エージングチェック用デバッグメニュー
    bool random_pointing_;                      ///< エージングチェック用デバッグフラグ
    
    
    
    //  ゲームスピード
    DebugMenuItem<float> dm_game_speed_;        ///< ゲームスピード
    float game_speed_;
    
    //  レイヤーのデバッグメニュー
    DebugMenuFrame  dm_layers_;             ///< デバッグメニュー
    Array<DebugMenuLabel*, 24> layer_list_; ///< デバッグメニューリスト

    bool exit_request_; ///< 終了リクエスト
    
};


TRI_CORE_NS_END


#endif // TRI_GAME_SYSTEM_HPP_INCLUDED
