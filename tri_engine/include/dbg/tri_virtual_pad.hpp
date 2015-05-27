/**
    @file tri_virtual_pad.hpp
    バーチャルパッド.
*/
#ifndef TRI_VIRTUAL_PAD_HPP_INCLUDED
#define TRI_VIRTUAL_PAD_HPP_INCLUDED

#include "gfx/tri_draw_layer.hpp"
#include "cross_sdk.hpp"

namespace t3 {


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
    
    const cross::GamePadData* getPadData() const {
        return &pad_data_;
    }
    
private:
    //  バーチャルパッド更新
    void updateVirtualPad();

    //  バーチャルパッド描画
    void renderVirtualPad();

    
    
private:
    //  バーチャルパッド用のレイヤー
    DrawLayer pad_layer_;
    
    //  パッド情報
    cross::GamePadData pad_data_;
};


}   // namespace t3





#endif // TRI_WORKBAR_HPP_INCLUDED