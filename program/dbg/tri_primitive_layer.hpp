

#ifndef TRI_PRIMITIVE_LAYER_HPP_INCLUDED
#define TRI_PRIMITIVE_LAYER_HPP_INCLUDED

#include "tri_render_layer.hpp"
#include <functional>


namespace t3 {
inline namespace gfx {


class PrimitiveLayer
    : public RenderLayer
{

public:
    PrimitiveLayer();
    virtual ~PrimitiveLayer();
    
private:
    virtual void updateLayer( tick_t tick ) override;
    virtual void drawLayer() override;
    
    
private:
    

};



}   // inline namespace gfx
}   // namespace t3





#endif //   TRI_PRIMITIVE_LAYER_HPP_INCLUDED

