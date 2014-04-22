
#ifndef TRI_DRAW_LAYER_HPP_INCLUDED
#define TRI_DRAW_LAYER_HPP_INCLUDED

#include <iostream>
#include <functional>
#include "tri_render_layer.hpp"
#include "../util/tri_method_callback.hpp"


namespace t3 {
inline namespace gfx {



class DrawLayer
    : public RenderLayer
{
    typedef DrawLayer self_t;
protected:
    typedef MethodCallback2<self_t, self_t* const, tick_t> UpdateCallback;
    typedef MethodCallback1<self_t, self_t* const> RenderCallback;

public:
    DrawLayer();
    explicit DrawLayer(const char* const name);
    virtual ~DrawLayer();
    
    template <typename T>
    void setUpdateCallback(
        T* instance,
        void (T::*update_func)(self_t*, tick_t)
    ){
        MethodCallback2<T, self_t*, tick_t> callback(instance, update_func);
        update_func_ = (UpdateCallback&)callback;
    }
    
    template <typename T>
    void setRenderCallback(
        T* instance,
        void (T::*render_func)(self_t*)
    ){
        MethodCallback1<T, self_t*> callback(instance, render_func);
        render_func_ = (RenderCallback&)callback;
    }
    
protected:
    void updateLayer(tick_t delta_time) override;
    void drawLayer() override;
    void nullUpdate(self_t* const, tick_t) {}
    void nullRender(self_t* const) {}
    
private:
    UpdateCallback update_func_;
    RenderCallback render_func_;
};



}   // inline namespace gfx
}   // namespace t3




#endif // TRI_DRAW_LAYER_HPP_INCLUDED
