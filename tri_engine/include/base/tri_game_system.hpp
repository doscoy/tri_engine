#ifndef TRI_GAME_SYSTEM_HPP_INCLUDED
#define TRI_GAME_SYSTEM_HPP_INCLUDED


#include "../dbg/tri_debugmenu.hpp"
#include "../kernel/tri_kernel.hpp"

#include "../util/random/tri_random.hpp"
#include "../util/tri_singleton.hpp"
#include "../gfx/tri_color.hpp"
#include "../gfx/tri_render_layer.hpp"
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
// ---------------------------------------------
//  ビューポート管理
    // *********************************************
    //  ビューポートを取得
    const Point2& getScreenSize() const {
        return screen_size_;
    }
    
    // *********************************************
    //  ビューポートを取得
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


    const Pad& getPad( const int pad_no = 0 ) const {
        return pad_.at(pad_no);
    }
    
    
    void registryToDebugMenu(DebugMenuFrame& parent_frame);
    
    
    void attachLayer( RenderLayer& layer );

    void detachLayer( RenderLayer& layer );

    RenderLayers& getLaysers() {
        return layers_;
    }
    
    const RenderLayers& getLayers() const {
        return layers_;
    }
    
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
    
    //  パッド入力
    std::array<Pad, MAX_PAD> pad_;

    //  描画レイヤー
    RenderLayers layers_;
    
    //  クリアカラー
    DebugMenuItem<int> dmi_color_idx_;
    int use_clear_color_index_;
    std::array<Color, 4> clear_colors_;
    
    //  レイヤーのデバッグメニュー
    t3::DebugMenuFrame  dmf_layers_;
    std::array<t3::DebugMenuLabel*, 24> layer_list_;

    
    bool suspend_;
};


}   // namespace base
}   // namespace t3


#endif // TRI_GAME_SYSTEM_HPP_INCLUDED
