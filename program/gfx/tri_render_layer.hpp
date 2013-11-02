
#ifndef TRI_RENDER_LAYER_HPP_INCLUDED
#define TRI_RENDER_LAYER_HPP_INCLUDED


#include "tri_develop_base.hpp"
#include "../util/tri_uncopyable.hpp"
#include "tri_debugmenu_items.hpp"
#include <list>

constexpr int LAYER_NAME_SIZE = 20;


namespace t3 {
inline namespace gfx {

    
class RenderLayer;
typedef std::list<RenderLayer*>   RenderLayers;


class RenderLayer
    : private Uncopyable
{
    friend void updateLayers(
                             RenderLayers& layers,
                             tick_t tick
                             );
    friend void drawLayers( RenderLayers& );
    
    
public:
    enum LayerPriority {
        PRIORITY_LOWEST     =  30,
        PRIORITY_BACK       =  60,
        PRIORITY_NORMAL     =  90,
        PRIORITY_FRONT      = 120,
        PRIORITY_CURTAIN    = 150,
        PRIORITY_DEBUG      = 180,
        PRIORITY_HIGHEST    = 210,
    };

public:
    RenderLayer( const char* const name, const int priority );
    explicit RenderLayer(const char* const name);
    virtual ~RenderLayer();

public:
    void setPriority( const int priority );
    
    int getPriority() const {
        return priority_;
    }
    
    void showLayer(){
        if ( !visible_ ){
            visible_ = true;
        }
    }
    
    void hideLayer() {
        if ( visible_ ){
            visible_ = false;
        }
    }
    
    bool isVisibleLayer() const {
        return visible_;
    }
    
    void pauseLayer(){
        if ( !pause_ ){
            pause_ = true;
        }
    }
    
    void resumeLayer(){
        if( pause_ ){
            pause_ = false;
        }
    }
    
    bool isPauseLayer() const {
        return pause_;
    }
    
    void setLayerName( const char* const name );
    
    const char* getLayerName() const {
        return layer_name_;
    }
    
    virtual void registryToDebugMenu(
        DebugMenuFrame& parent
    );
    
    virtual void unregistryToDebugMenu();
    
protected:
    virtual void updateLayer( tick_t tick ) = 0;
    virtual void drawLayer() = 0;

    
protected:
    bool pause_;
    bool visible_;
    uint8_t priority_;
    char layer_name_[LAYER_NAME_SIZE];

    //  デバッグメニュー登録
    DebugMenuFrame dmf_me_;
    DebugMenuItem<bool> dmi_visible_;
    DebugMenuItem<bool> dmi_pause_;
};


//  レイヤー更新
void updateLayers(
    RenderLayers& layers,
    tick_t tick
);

void drawLayers(
    RenderLayers& layers
);




}   // inline namespace gfx
}   // namespace t3


#endif // TRI_RENDER_LAYER_HPP_INCLUDED

