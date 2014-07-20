#ifndef TRI_GAME_SYSTEM_HPP_INCLUDED
#define TRI_GAME_SYSTEM_HPP_INCLUDED

#include "tri_event_manager.hpp"
#include "tri_task_manager.hpp"
#include "dbg/tri_debugmenu.hpp"
#include "dbg/tri_debug_log_layer.hpp"
#include "kernel/tri_kernel.hpp"
#include "util/random/tri_random.hpp"
#include "util/tri_singleton.hpp"
#include "gfx/tri_color.hpp"
#include "gfx/tri_render_layer.hpp"
#include "gfx/tri_fade_layer.hpp"
#include <array>



//==============================================================================
namespace t3 {
inline namespace base {


constexpr int MAX_PAD = 4;

class Director 
    : public Singleton<Director>
{
    friend class Singleton;

public:
    typedef RandomNumberGenerator<RandomWell> random_t;
    

private:
    Director();
    ~Director();

public:
    void initializeGameSystem();
    void terminategameSystem();
    
// ---------------------------------------------
//  ビューポート管理
    
    //  スクリーンサイズを設定
    void setScreenSize(const Vec2& vp) {
        screen_size_ = vp;
    }
    
    
// ---------------------------------------------
//  乱数管理    
    
    //  乱数ジェネレータを取得
    random_t& random(){
        return random_number_generator_;
    }
    

    void update(
        const tick_t delta_time
    );
    
    void suspend(
        const tick_t delta_time
    );
    
    bool isSuspend() const {
        return suspend_;
    }

    void setSuspend( const bool suspend ){
        suspend_ = suspend;
    }
    
    void updateInput(
        const tick_t delta_time
    );
    
    
    void registryToDebugMenu(DebugMenuFrame& parent_frame);
    
    

    RenderLayers& layers() {
        return layers_;
    }
    
    const RenderLayers& layers() const {
        return layers_;
    }
    
    bool isExitRequest() const {
        return exit_request_;
    }
    //  レイヤーの登録
    void attachLayer(RenderLayer* layer);
    
    //  レイヤーの削除
    void detachLayer(RenderLayer* layer);
    
    float getGameSpeed() const {
        return game_speed_;
    }
    
    
    void showTask() const;
    
public:
    static void addSystemTask(std::shared_ptr<Task> task);
    
    static const Input& input(const int player_no = 0);
    
    static RenderLayer* findLayer(const std::string& layer_name);
    
    static Vec2 screenToViewport(const Vec2& screen_pos);
    
    static Vec2 viewportToScreen(const Vec2& viewport_pos);
    
    static bool isOutOfScreen(const Vec2& screen_pos);
    
    static void setupBlackOut();
    static void setupBlackIn();
    
    static void fadeOut();
    
    static void fadeIn();
    
    static bool isFadeEnd();
    
    static bool isFadeInEnd();
    
    static bool isFadeOutEnd();
    
    static const Vec2& getScreenSize();
    
    static void printLog(const char* const buf);
    
    static void printDisplay(
        int x,
        int y,
        const uint32_t color,
        const int font_size,
        const char* const buf
    );
    
private:
    void clearColor();


    //  デバッグメニューにレイヤー登録するコールバック
    void registryLayersToDebugMenu();
    void unregistryLayersToDebugMenu();
    
private:
    //  デバッグ用レイヤー
    std::unique_ptr<DebugLogLayer> log_layer_;
    std::unique_ptr<DebugStringLayer> dbg_screen_layer_;

    //  システムフェード
    std::unique_ptr<FadeLayer> fade_layer_;
    
    //  乱数
    random_t random_number_generator_;

    //  ビューポート
    Vec2 screen_size_;
    
    //  インプットデータ
    std::array<Input, MAX_PAD> input_;

    //  描画レイヤー
    RenderLayers layers_;
    
    
    
    //  イベントマネージャ
    EventManager event_manager_;
    
    //  タスクマネージャ
    TaskManager task_manager_;
    
    
    //  クリアカラー
    DebugMenuItem<int> dm_color_idx_;
    int use_clear_color_index_;
    std::array<Color, 4> clear_colors_;
    
    //  エージング用ランダムタッチ
    DebugMenuItem<bool> dm_random_pointing_;
    bool random_pointing_;
    
    
    
    //  ゲームスピード
    DebugMenuItem<float> dm_game_speed_;
    float game_speed_;
    
    //  レイヤーのデバッグメニュー
    DebugMenuFrame  dm_layers_;
    std::array<DebugMenuLabel*, 24> layer_list_;

    bool exit_request_;
    
    bool suspend_;
    
};


}   // namespace base
}   // namespace t3


#endif // TRI_GAME_SYSTEM_HPP_INCLUDED
