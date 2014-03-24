#ifndef TRI_GAME_SYSTEM_HPP_INCLUDED
#define TRI_GAME_SYSTEM_HPP_INCLUDED


#include "dbg/tri_debugmenu.hpp"
#include "kernel/tri_kernel.hpp"
#include "util/random/tri_random.hpp"
#include "util/tri_singleton.hpp"
#include "gfx/tri_color.hpp"
#include "gfx/tri_render_layer.hpp"
#include <array>



//==============================================================================
namespace t3 {
inline namespace base {


constexpr int MAX_PAD = 4;

class GameSystem 
    : public Singleton<GameSystem>
{
    friend class Singleton;

public:
    typedef RandomNumberGenerator<RandomWell> random_t;
    

private:
    GameSystem();
    ~GameSystem();

public:
    void initializeGameSystem();

// ---------------------------------------------
//  ビューポート管理
    // *********************************************
    //  スクリーンサイズを取得
    const Point2& getScreenSize() const {
        return screen_size_;
    }
    
    // *********************************************
    //  スクリーンサイズを設定
    void setScreenSize( const Point2& vp ) {
        screen_size_ = vp;
    }
    
// ---------------------------------------------
//  乱数管理    
    // *********************************************
    //  乱数ジェネレータを取得
    random_t& getRandomNumberGenerator(){
        return random_number_generator_;
    }
    

    void update( tick_t tick );
    void suspend( tick_t tick );
    bool isSuspend() const {
        return suspend_;
    }

    void setSuspend( const bool suspend ){
        suspend_ = suspend;
    }


    const Input& getInput(const int pad_no = 0) const {
        return input_.at(pad_no);
    }
    
    
    void registryToDebugMenu(DebugMenuFrame& parent_frame);
    
    

    RenderLayers& getLaysers() {
        return layers_;
    }
    
    const RenderLayers& getLayers() const {
        return layers_;
    }
    
    bool isExitRequest() const {
        return exit_request_;
    }
    //  レイヤーの登録
    void attachLayer(RenderLayer* layer);
    
    //  レイヤーの削除
    void detachLayer(RenderLayer* layer);
    
private:
    void setClearColor();


    //  デバッグメニューにレイヤー登録するコールバック
    void registryLayersToDebugMenu();
    void unregistryLayersToDebugMenu();
    
private:
    //  乱数
    random_t random_number_generator_;

    //  ビューポート
    Point2 screen_size_;
    
    //  インプットデータ
    std::array<Input, MAX_PAD> input_;

    //  描画レイヤー
    RenderLayers layers_;
    
    //  クリアカラー
    DebugMenuItem<int> dmi_color_idx_;
    int use_clear_color_index_;
    std::array<Color, 4> clear_colors_;
    
    //  レイヤーのデバッグメニュー
    t3::DebugMenuFrame  dmf_layers_;
    std::array<t3::DebugMenuLabel*, 24> layer_list_;

    bool exit_request_;
    
    bool suspend_;
};


}   // namespace base
}   // namespace t3


#endif // TRI_GAME_SYSTEM_HPP_INCLUDED
