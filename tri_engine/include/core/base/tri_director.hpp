/**
    @file tri_director.hpp
    ゲームシステム管理.
*/

#ifndef TRI_GAME_SYSTEM_HPP_INCLUDED
#define TRI_GAME_SYSTEM_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_event_manager.hpp"
#include "tri_task_manager.hpp"
#include "core/debug/tri_debugmenu.hpp"
#include "core/debug/tri_debug_log_layer.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/utility/random/tri_random.hpp"
#include "core/utility/tri_singleton.hpp"
#include "core/graphics/tri_color.hpp"
#include "core/graphics/tri_render_layer.hpp"
#include "core/graphics/tri_fade_layer.hpp"
#include "core/graphics/tri_sprite_layer.hpp"
#include <array>



TRI_CORE_NS_BEGIN


constexpr float VIRTUAL_SCREEN_WIDTH = 640.0f; ///< ゲーム内仮想スクリーンサイズ幅
constexpr float VIRTUAL_SCREEN_HEIGHT = 1136.0f; ///< ゲーム内仮想スクリーンサイズ高さ

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
    /// デバイスのスクリーンサイズ設定
    void deviceScreenSize(const Vec2& vp) {
        device_screen_size_ = vp;
        calcScreenRevise();
    }
    
    ///
    /// デバイスのスクリーンサイズ取得
    const Vec2& deviceScreenSize() const {
        return device_screen_size_;
    }
    
    ///
    /// 仮想スクリーンサイズ設定
    void virtualScreenSize(const Vec2 screen) {
        virtual_screen_size_ = screen;
        calcScreenRevise();
    }
    
    ///
    /// 仮想スクリーンサイズ取得
    const Vec2& virtualScreenSize() const {
        return virtual_screen_size_;
    }
    
    ///
    /// スクリーンの補正値取得
    const Vec2& screenRevise() const {
        return screen_revise_;
    }
    
// ---------------------------------------------
//  乱数管理    
    
    ///
    /// 乱数ジェネレータ取得
    random_t& random(){
        return random_number_generator_;
    }
    

    ///
    /// 通常の更新
    void update(
        const tick_t delta_time
    );
    
    ///
    /// サスペンドの更新
    void suspend(
        const tick_t delta_time
    );
    
    ///
    /// サスペンド判定
    bool isSuspend() const {
        return suspend_;
    }

    ///
    /// サスペンド設定
    void setSuspend( const bool suspend ){
        suspend_ = suspend;
    }
    
    ///
    /// 入力更新
    void updateInput(
        const tick_t delta_time
    );
    
    
    ///
    /// デバッグメニュー登録
    void registryToDebugMenu(DebugMenuFrame& parent_frame);
    
    

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
    
public:

    ///
    /// クリアカラー取得
    static const Color& getClearColor();

    ///
    /// クリアカラー設定
    static void setClearColor(const Color& c);

    ///
    /// システムタスク登録
    static void addSystemTask(SharedPtr<Task> task);
    

    ///
    /// 入力情報を取得
    static const Input& input(const int player_no = 0);
    
    ///
    /// 登録されている指定レイヤーを探す
    static LayerBase* findLayer(const String& layer_name);
    
    ///
    /// ビューポートの位置に変換
    static Vec2 screenToViewport(const Vec2& screen_pos);
    
    ///
    /// スクリーンのピクセル位置へ変換
    static Vec2 viewportToScreen(const Vec2& viewport_pos);
    
    ///
    /// スクリーン外判定
    static bool isOutOfScreen(const Vec2& screen_pos);
    
    ///
    /// ブラックアウト設定
    static void setupBlackOut();

    ///
    /// ブラックイン設定
    static void setupBlackIn();
    
    ///
    /// フェードアウト
    static void fadeOut();
    
    ///
    /// フェードイン
    static void fadeIn();
    
    ///
    /// フェード終了判定
    static bool isFadeEnd();
    
    ///
    /// フェードイン終了判定
    static bool isFadeInEnd();
    
    ///
    /// フェードアウト終了判定
    static bool isFadeOutEnd();
    
    ///
    /// スクリーンサイズ取得
    static const Vec2& screenSize();
    
    ///
    /// 画面にログを登録
    static void printLog(const char* const buf);
    
    ///
    /// 画面にデバッグ文字を描画
    static void printDisplay(
        const float x,
        const float y,
        const uint32_t color,
        const int font_size,
        const char* const str
    );
        
private:
    
    ///
    /// スクリーン計算
    void calcScreenRevise();

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
    ScopedPtr<DebugLogLayer> log_layer_;                ///< デバッグログ用レイヤー
    ScopedPtr<DebugStringLayer> dbg_screen_layer_;      ///< デバッグプリント用レイヤー
    ScopedPtr<SpriteLayer> dbg_print_layer_;
    ScopedPtr<DebugStringBuffer> dbg_print_buffer_;

    //  システムフェード
    ScopedPtr<FadeLayer> fade_layer_;   ///< フェードレイヤー
    
    //  乱数
    random_t random_number_generator_;  ///< 乱数生成器

    //   スクリーンサイズ
    Vec2 device_screen_size_;           ///< デバイススクリーンサイズ
    Vec2 virtual_screen_size_;          ///< 仮想スクリーンサイズ
    Vec2 screen_revise_;
    
    //  インプットデータ
    Array<Input, MAX_PAD> input_;   ///< 入力データ

    //  描画レイヤー
    Layers layers_;           ///<  描画レイヤー
    
    
    
    //  イベントマネージャ
    EventManager event_manager_;    ///< イベントマネージャ
    
    //  タスクマネージャ
    TaskManager task_manager_;      ///< タスクマネージャ
    
    
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
    bool suspend_;      ///< サスペンドフラグ
    
};


TRI_CORE_NS_END


#endif // TRI_GAME_SYSTEM_HPP_INCLUDED
