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
#include "core/graphics/layer/tri_layer_base.hpp"
#include "core/utility/tri_method_callback.hpp"


TRI_CORE_NS_BEGIN



///
/// 描画レイヤー
class DrawLayer;
using DrawLayerPtr = SharedPtr<DrawLayer>;
class DrawLayer
    : public LayerBase
{
protected:
    ///
    /// コンストラクタ
    DrawLayer(
        const String& name, 
        const Priority priority
    );
public:

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
        update_func_.reset(new MethodCallback<T>(instance, callback));
    }
    
    ///
    /// 描画コールバック設定
    template <typename T>
    void setRenderCallback(
        T* instance,
        void (T::*callback)()
    ) {
        render_func_.reset(new MethodCallback<T>(instance, callback));
    }
    
protected:
    ///
    /// レイヤーの更新
    void updateLayer(const FrameInfo& frame_info) override;

    ///
    /// レイヤーの描画
    void renderLayer() override;

public:
    static DrawLayerPtr create(
        const String& name = "Draw", 
        const Priority priority = Priority::DEFAULT
    ) {
        DrawLayerPtr layer(T3_SYS_NEW DrawLayer(name, priority));
        layer->setupRenderTargetToSystem();
        return layer;
    }
    
private:
    UniquePtr<MethodCallbackBase> update_func_;    ///< アップデート時コールバック関数
    UniquePtr<MethodCallbackBase> render_func_;    ///< 描画時コールバック関数
};



TRI_CORE_NS_END




#endif // TRI_DRAW_LAYER_HPP_INCLUDED
