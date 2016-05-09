////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_trace.hpp
    デバッグトレース.
*/


#ifndef TRI_DEBUG_STRING_LAYER_HPP_INCLUDED
#define TRI_DEBUG_STRING_LAYER_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include "cross/cross_std.hpp"
#include "core/graphics/tri_sprite_layer.hpp"
#include "tri_debug_string_buffer.hpp"



TRI_CORE_NS_BEGIN


///
/// デバッグ文字表示レイヤー
class DebugStringLayer
    : public SpriteLayer
{
public:
    ///
    /// コンストラクタ
    DebugStringLayer(
        const String& name,                     ///< レイヤー名
        const LayerBase::Priority priority      ///< プライオリティ
    );
    
    ///
    /// デストラクタ
    ~DebugStringLayer();
    
    
    
public:
    ///
    /// 文字列追加
    void addString(
        const float x,
        const float y,
        const rgba32_t color,
        const int size,
        const char* const str
    ) {
        buffer_.addString(x, y, color, size, str);
    }
    
protected:
    ///
    /// レイヤ更新
    void updateLayer(const FrameInfo& frame_info) override;
    

private:
    ///
    /// スプライト再構築
    void resetSprites();

private:
    DebugStringBuffer buffer_;
    Vector<SpritePtr> sprites_;
    
    TexturePtr font_sheet_;


};


TRI_CORE_NS_END




#endif  // TRI_DEBUG_STRING_LAYER_HPP_INCLUDED
