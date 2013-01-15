
#ifndef TRI_RENDER_LAYER_HPP_INCLUDED
#define TRI_RENDER_LAYER_HPP_INCLUDED


#include "tri_develop_base.hpp"



#define LAYER_NAME_SIZE (20)


namespace t3 {
inline namespace gfx {

class RenderLayer{
public:
    enum LayerPriority {
        PRIORITY_LOWEST     =  30,
        PRIORITY_BACK       =  60,
        PRIORITY_NORMAL     =  90,
        PRIORITY_FRONT      = 120,
        PRIORITY_HIGHEST    = 150,
    };

public:
    RenderLayer();
    virtual ~RenderLayer();

public:
    void updateLayer( tick_t tick ){}
    void drawLayer(){}
    
    void setPriority( const int priority );
    
    int getPriority() const {
        return priority_;
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
    
    void setLayerName( const char* const name );
    
private:
    bool pause_;
    u_char priority_;
    char layer_name_[LAYER_NAME_SIZE];

};


}   // inline namespace gfx
}   // namespace t3


#endif // TRI_RENDER_LAYER_HPP_INCLUDED

