////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file jet_numbers.hpp
    数値グラフィックス.
*/

#ifndef JET_NUMBERS_HPP_INCLUDED
#define JET_NUMBERS_HPP_INCLUDED

//  include
#include "jet/jet_config.hpp"
#include "core/math/tri_vec2.hpp"
#include "core/graphics/tri_sprite_layer.hpp"
#include "core/base/tri_font_glyph.hpp"
#include "core/geometry/tri_transform.hpp"
#include "core/utility/tri_utf8.hpp"

TRI_JET_NS_BEGIN

///
/// 数値
class Number {
    
public:
    Number();
    ~Number();

public:
    ///
    /// 使用するテクスチャと、0-9の値に対応するUVを設定
    void initialize(
        const TexturePtr& tex,
        const TextureUV& uv0,
        const TextureUV& uv1,
        const TextureUV& uv2,
        const TextureUV& uv3,
        const TextureUV& uv4,
        const TextureUV& uv5,
        const TextureUV& uv6,
        const TextureUV& uv7,
        const TextureUV& uv8,
        const TextureUV& uv9
    );
    
    ///
    /// 数値設定
    void value(int number);

    ///
    /// トランスフォーム取得
    auto sprite() {
        return sprite_;
    }

    const auto sprite() const {
        return sprite_;
    }

private:
    SpritePtr sprite_;
    TextureUV uv_[10];    // 0-9
};




///
/// 複数桁数値
class Numbers {
public:
    Numbers();
    ~Numbers();

public:
    ///
    /// 初期化
    /// 数値が横に並ぶだけのテクスチャなのでUVは自動計算
    void initialize(
        int digit,      //< 桁数
        const TexturePtr& tex,
        const Vec2& size
    );
    
    ///
    /// 初期化
    void initialize(
        int digit,      //< 桁数
        const TexturePtr& tex,
        const Vec2& size,
        const TextureUV& uv0,
        const TextureUV& uv1,
        const TextureUV& uv2,
        const TextureUV& uv3,
        const TextureUV& uv4,
        const TextureUV& uv5,
        const TextureUV& uv6,
        const TextureUV& uv7,
        const TextureUV& uv8,
        const TextureUV& uv9
    );

    ///
    /// 中央寄せ
    void alignCenter();

private:
    Vector<Number> numbers_;
    Transform2DPtr transform_;
};




TRI_JET_NS_END


#endif // JET_NUMBERS_HPP_INCLUDED
