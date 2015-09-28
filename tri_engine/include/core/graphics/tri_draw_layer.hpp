////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_draw_layer.hpp
    描画レイヤー.
*/

#ifndef TRI_DRAW_LAYER_HPP_INCLUDED
#define TRI_DRAW_LAYER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include <iostream>
#include <functional>
#include "tri_render_layer.hpp"
#include "../utility/tri_method_callback.hpp"


TRI_CORE_NS_BEGIN



///
/// 描画レイヤー
class DrawLayer
    : public LayerBase
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
        void (T::*callback)()
    ) {
        update_func_.reset(new MethodCallbackX<T>(instance, callback));
    }
    
    ///
    /// 描画コールバック設定
    template <typename T>
    void setRenderCallback(
        T* instance,
        void (T::*callback)()
    ) {
        render_func_.reset(new MethodCallbackX<T>(instance, callback));
    }
    
protected:
    ///
    /// レイヤーの更新
    void updateLayer(tick_t delta_time) override;

    ///
    /// レイヤーの描画
    void drawLayer() override;

    
private:
    ScopedPtr<MethodCallbackBaseX> update_func_;    ///< アップデート時コールバック関数
    ScopedPtr<MethodCallbackBaseX> render_func_;    ///< 描画時コールバック関数
};



TRI_CORE_NS_END




#endif // TRI_DRAW_LAYER_HPP_INCLUDED
