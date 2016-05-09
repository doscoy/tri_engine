////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_debug_log_layer.hpp
    デバッグログレイヤー.
*/

#ifndef TRI_DEBUG_LOG_LAYER_HPP_INCLUDED
#define TRI_DEBUG_LOG_LAYER_HPP_INCLUDED

#include "core/core_config.hpp"
#include "tri_debug_log_buffer.hpp"
#include "core/debug/tri_debug_string_layer.hpp"

TRI_CORE_NS_BEGIN



///
/// デバッグ用ログ表示レイヤー
class DebugLogLayer
    : public DebugStringLayer
{
public:
    ///
    /// コンストラクタ
    DebugLogLayer(
        const String& name,                         ///< レイヤー名
        const LayerBase::Priority priority          ///< プライオリティ
    );

    ///
    /// デストラクタ
    virtual ~DebugLogLayer();

public:
    ///
    /// レイヤーにログを追加
    void addLog(
        const char* const str
    ) {
        buffer_.addString(str);
    }
    
    ///
    /// ログレイヤをスクロール
    void slideUp();

    ///
    /// ログレイヤをスクロール
    void slideDown();
    
    
protected:
    ///
    /// レイヤ更新
    void updateLayer(const FrameInfo& frame_info) override;

protected:
    DebugLogBuffer buffer_;   ///< ログバッファ
    int log_show_offset_;               ///< 表示用オフセット
};


TRI_CORE_NS_END


#endif  // TRI_DEBUG_LOG_LAYER_HPP_INCLUDED
