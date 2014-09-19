
#ifndef TRI_RENDER_LAYER_HPP_INCLUDED
#define TRI_RENDER_LAYER_HPP_INCLUDED


#include "util/tri_uncopyable.hpp"
#include "util/tri_nameable.hpp"
#include "dbg/tri_debugmenu_items.hpp"
#include <list>



namespace t3 {
inline namespace gfx {

    
class RenderLayer;
typedef List<RenderLayer*>   RenderLayers;


class RenderLayer
    : private Uncopyable
    , virtual public Nameable
{
public:
    enum LayerPriority {
        PRIORITY_LOWEST     =  20, // 奥
        PRIORITY_SYS_BACK   =  60,
        PRIORITY_APP_BACK   =  60,
        PRIORITY_APP_NORMAL =  90,
        PRIORITY_APP_FRONT  = 120,
        PRIORITY_SYS_FRONT  = 150,
        PRIORITY_SYS_FADE   = 170,
        PRIORITY_DEBUG      = 180,
        PRIORITY_HIGHEST    = 240, // 手前
    };
    
public:
    RenderLayer(const String& name, const int priority);
    explicit RenderLayer(const String& name);
    virtual ~RenderLayer();

public:
    void priority(const int priority);
    
    int priority() const {
        return priority_;
    }
    
    void showLayer(){
        if (!visible_){
            visible_ = true;
        }
    }
    
    void hideLayer() {
        if (visible_) {
            visible_ = false;
        }
    }
    
    bool isVisibleLayer() const {
        return visible_;
    }
    
    void pauseLayer() {
        if (!pause_) {
            pause_ = true;
        }
    }
    
    void resumeLayer() {
        if (pause_){
            pause_ = false;
        }
    }
    
    
    void enableLayer() {
        showLayer();
        resumeLayer();
    }
    
    void disableLayer() {
        hideLayer();
        pauseLayer();
    }
    
    
    bool isPauseLayer() const {
        return pause_;
    }
    
    virtual void registryToDebugMenu(
        DebugMenuFrame& parent
    );
    
    virtual void unregistryToDebugMenu();
    
    
    
public:
    //  レイヤー更新
    static void updateLayers(
        RenderLayers& layers,
        tick_t delta_time
    );
    
    static void drawLayers(
        RenderLayers& layers
    );
    
protected:
    virtual void updateLayer(tick_t delta_time){};
    virtual void drawLayer(){};

    void attachSystem();
    void detachSystem();

    
protected:
    bool pause_;
    bool visible_;
    uint8_t priority_;

    //  デバッグメニュー登録
    DebugMenuFrame dmf_me_;
    DebugMenuItem<bool> dmi_visible_;
    DebugMenuItem<bool> dmi_pause_;
};







}   // inline namespace gfx
}   // namespace t3


#endif // TRI_RENDER_LAYER_HPP_INCLUDED

