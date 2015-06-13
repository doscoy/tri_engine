/**
    @file tri_debug_string_layer.hpp
    デバッグ文字列表示レイヤー.
*/

#ifndef TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED
#define TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "../graphics/tri_render_layer.hpp"
#include "tri_debug_string_buffer.hpp"
#include "../graphics/tri_color.hpp"

TRI_CORE_NS_BEGIN

///
/// デバッグ文字表示レイヤ
class DebugStringLayer
    : public RenderLayer
{
public:
    ///
    /// コンストラクタ
    DebugStringLayer(const char* const name = "DEBUG SCREEN");

    ///
    /// デストラクタ
    virtual ~DebugStringLayer();

public:
    ///
    /// 文字追加
    void writeString(
        const float x,
        const float y,
        const uint32_t color,
        const int size,
        const char* const str
    );

protected:
    ///
    /// 更新関数
    void updateLayer(tick_t delta_time) override;

    ///
    /// 描画関数
    void drawLayer() override;


protected:
    DebugStringBuffer debug_string_buffer_; ///<  文字列保存用バッファ

};



TRI_CORE_NS_END


#endif // TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

