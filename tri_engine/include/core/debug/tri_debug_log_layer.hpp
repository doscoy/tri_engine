/**
    @file tri_debug_log_layer.hpp
    デバッグログレイヤー.
*/

#ifndef TRI_DEBUG_LOG_LAYER_HPP_INCLUDED
#define TRI_DEBUG_LOG_LAYER_HPP_INCLUDED

#include "core/core_config.hpp"
#include "tri_debug_log_buffer.hpp"


TRI_CORE_NS_BEGIN



///
/// デバッグ用ログ表示レイヤー
class DebugLogLayer
    : public DebugStringLayer
{
public:
    ///
    /// コンストラクタ
    DebugLogLayer(const char* const name = "DISPLAY LOG");

    ///
    /// デストラクタ
    virtual ~DebugLogLayer();

public:
    ///
    /// レイヤーにログを追加
    void writeString(
        const char* const str
    );
    
    ///
    /// ログレイヤをスクロール
    void slideUp();

    ///
    /// ログレイヤをスクロール
    void slideDown();
    
    
protected:
    ///
    /// レイヤ更新
    void updateLayer(tick_t delta_time) override;

    ///
    /// レイヤ描画
    void drawLayer() override;
    
    ///
    /// ログの現在の表示行を取得
    int getLogShowLineIndex() const;

protected:
    DebugLogBuffer debug_log_buffer_;   ///< ログバッファ
    int log_show_offset_;               ///< 表示用オフセット
};


TRI_CORE_NS_END


#endif  // TRI_DEBUG_LOG_LAYER_HPP_INCLUDED
