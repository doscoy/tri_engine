
#ifndef TRI_RENDER_LAYER_HPP_INCLUDED
#define TRI_RENDER_LAYER_HPP_INCLUDED


#include "util/tri_uncopyable.hpp"
#include "util/tri_nameable.hpp"
#include "dbg/tri_debugmenu_items.hpp"
#include <list>



namespace t3 {
inline namespace gfx {

class Surface;
class RenderLayer;
using RenderLayers = List<RenderLayer*>;


class RenderLayer
    : private Uncopyable
    , virtual public Nameable
{
public:
    enum LayerPriority {
        PRIORITY_LOWEST      =  20, // 奥
        PRIORITY_SYS_BACK    =  50,
        PRIORITY_APP_BACK1   =  61,
        PRIORITY_APP_BACK2   =  62,
        PRIORITY_APP_BACK3   =  63,
        PRIORITY_APP_BACK4   =  64,
        PRIORITY_APP_BACK5   =  65,
        PRIORITY_APP_DEFAULT =  90,
        PRIORITY_APP_FRONT1  = 101,
        PRIORITY_APP_FRONT2  = 102,
        PRIORITY_APP_FRONT3  = 103,
        PRIORITY_APP_FRONT4  = 104,
        PRIORITY_APP_FRONT5  = 104,
        PRIORITY_APP_UI      = 110,
        PRIORITY_SYS_FRONT   = 150,
        PRIORITY_SYS_FADE    = 170,
        PRIORITY_DEBUG       = 180,
        PRIORITY_HIGHEST     = 240, // 手前
    };
    
public:
    RenderLayer(const String& name, const int priority);
    explicit RenderLayer(const String& name);
    virtual ~RenderLayer();

public:

    void renderTarget(
        Surface* target
    ) {
        render_target_ = target;
    }
    
    const Surface* renderTarget() const {
        return render_target_;
    }


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
    
    void callDraw();
    void attachSystem();
    void detachSystem();

    
protected:
    bool pause_;
    bool visible_;
    uint8_t priority_;
    Surface* render_target_;


    //  デバッグメニュー登録
    DebugMenuFrame dmf_me_;
    DebugMenuItem<bool> dmi_visible_;
    DebugMenuItem<bool> dmi_pause_;
};







}   // inline namespace gfx
}   // namespace t3


#endif // TRI_RENDER_LAYER_HPP_INCLUDED

