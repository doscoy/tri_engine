
#ifndef TRI_DRAW_LAYER_HPP_INCLUDED
#define TRI_DRAW_LAYER_HPP_INCLUDED

//  include
#include <iostream>
#include <functional>
#include "tri_render_layer.hpp"
#include "../util/tri_method_callback.hpp"


namespace t3 {


///
/// 描画レイヤー
class DrawLayer
    : public RenderLayer
{
    using self_t = DrawLayer;
protected:
    using UpdateCallback = MethodCallback2<self_t, self_t* const, tick_t>;  ///< 更新コールバック型
    using RenderCallback = MethodCallback1<self_t, self_t* const>;          ///< 描画コールバック型

public:
    ///
    /// コンストラクタ
    DrawLayer();

    ///
    /// コンストラクタ
    explicit DrawLayer(const String name, const int priority);

    ///
    /// デストラクタ
    virtual ~DrawLayer();
    
    ///
    /// 更新コールバック設定
    template <typename T>
    void setUpdateCallback(
        T* instance,
        void (T::*update_func)(self_t*, tick_t)
    ){
        MethodCallback2<T, self_t*, tick_t> callback(instance, update_func);
        update_func_ = (UpdateCallback&)callback;
    }
    
    ///
    /// 描画コールバック設定
    template <typename T>
    void setRenderCallback(
        T* instance,
        void (T::*render_func)(self_t*)
    ){
        MethodCallback1<T, self_t*> callback(instance, render_func);
        render_func_ = (RenderCallback&)callback;
    }
    
protected:
    ///
    /// レイヤーの更新
    void updateLayer(tick_t delta_time) override;

    ///
    /// レイヤーの描画
    void drawLayer() override;

    ///
    /// 何もしない更新コールバック
    void nullUpdate(self_t* const, tick_t) {}

    ///
    /// 何もしない描画コールバック
    void nullRender(self_t* const) {}
    
private:
    UpdateCallback update_func_;    ///< アップデート時コールバック関数
    RenderCallback render_func_;    ///< 描画時コールバック関数
};



}   // namespace t3




#endif // TRI_DRAW_LAYER_HPP_INCLUDED
