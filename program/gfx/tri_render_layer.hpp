
#ifndef TRI_RENDER_LAYER_HPP_INCLUDED
#define TRI_RENDER_LAYER_HPP_INCLUDED


#include "tri_develop_base.hpp"

namespace t3 {
    

class RenderLayer{
public:
    RenderLayer();
    ~RenderLayer();

public:
    void render();
    
    void setPriority( const int priority ){
        priority_ = priority;
    }

private:
    int priority_;
    
    
};


    
} // namespace t3


#endif // TRI_RENDER_LAYER_HPP_INCLUDED

