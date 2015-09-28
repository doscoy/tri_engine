////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_virtual_pad.hpp
    バーチャルパッド.
*/
#ifndef TRI_VIRTUAL_PAD_HPP_INCLUDED
#define TRI_VIRTUAL_PAD_HPP_INCLUDED

#include "core/core_config.hpp"
#include "cross/cross_sdk.hpp"
#include "core/graphics/tri_draw_layer.hpp"

TRI_CORE_NS_BEGIN



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


TRI_CORE_NS_END




#endif // TRI_WORKBAR_HPP_INCLUDED