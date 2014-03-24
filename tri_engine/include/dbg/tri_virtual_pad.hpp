#ifndef TRI_VIRTUAL_PAD_HPP_INCLUDED
#define TRI_VIRTUAL_PAD_HPP_INCLUDED

#include "gfx/tri_draw_layer.hpp"
#include "platform/platform_types.hpp"


namespace t3 {
inline namespace dbg {


class VirtualPad
    : private Uncopyable
{
public:
    //  コンストラクタ
    VirtualPad();
    
    //  デストラクタ
    ~VirtualPad();


public:
    //  表示
    void open();

    //  しまう
    void close();
    
    const GamePadData* getPadData() const {
        return &pad_data_;
    }
    
private:
    //  バーチャルパッド更新
    void updateVirtualPad(t3::DrawLayer* const layer, tick_t tick);

    //  バーチャルパッド描画
    void renderVirtualPad(t3::DrawLayer* const layer);

    
    
private:
    //  バーチャルパッド用のレイヤー
    DrawLayer pad_layer_;
    
    //  パッド情報
    GamePadData pad_data_;
};


}   // inline namespace dbg
}   // namespace t3





#endif // TRI_WORKBAR_HPP_INCLUDED