/**
    @file tri_draw_layer.hpp
    描画レイヤー.
*/

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
        std::function<void(T&)> call
    ) {
        update_func_.reset(new MethodCallbackX<T>(instance, call));
    }
    
    ///
    /// 描画コールバック設定
    template <typename T>
    void setRenderCallback(
        T* instance,
        std::function<void(T&)> call
    ) {
        render_func_.reset(new MethodCallbackX<T>(instance, call));
    }
    
protected:
    ///
    /// レイヤーの更新
    void updateLayer(tick_t delta_time) override;

    ///
    /// レイヤーの描画
    void drawLayer() override;

    
private:
    t3::ScopedPtr<MethodCallbackBaseX> update_func_;    ///< アップデート時コールバック関数
    t3::ScopedPtr<MethodCallbackBaseX> render_func_;    ///< 描画時コールバック関数
};



}   // namespace t3




#endif // TRI_DRAW_LAYER_HPP_INCLUDED
