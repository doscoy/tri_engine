////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  include
#include "jet/gui/jet_numbers.hpp"

TRI_JET_NS_BEGIN

///
/// コンストラクタ
Number::Number()
    : sprite_()
    , uv_()
{}

///
/// デストラクタ
Number::~Number()
{}

///
/// 初期化
void Number::initialize(
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
) {
    sprite_ = t3::Sprite::create(tex);

    uv_[0] = uv0;
    uv_[1] = uv1;
    uv_[2] = uv2;
    uv_[3] = uv3;
    uv_[4] = uv4;
    uv_[5] = uv5;
    uv_[6] = uv6;
    uv_[7] = uv7;
    uv_[8] = uv8;
    uv_[9] = uv9;
}

///
/// 数値設定
void Number::value(
    int number
) {
    T3_ASSERT_RANGE(number, 0, 9);
    sprite_->textureCoord(uv_[number]);
}




///
/// コンストラクタ
Numbers::Numbers()
    : numbers_()
    , transform_()
{}


///
/// デストラクタ
Numbers::~Numbers()
{}


///
/// 初期化
void Numbers::initialize(
    int digit,              //< 桁数
    const TexturePtr& tex,   //< 使用テクスチャ
    const Vec2& size
) {
    //
    //  0-9 までの数字のみ書かれたテクスチャと仮定して
    //  それぞれのUVを計算
    TextureUV uv[10] = {
        {0.0f, 0.0f, 0.1f, 1.0f},
        {0.1f, 0.0f, 0.2f, 1.0f},
        {0.2f, 0.0f, 0.3f, 1.0f},
        {0.3f, 0.0f, 0.4f, 1.0f},
        {0.4f, 0.0f, 0.5f, 1.0f},
        {0.5f, 0.0f, 0.6f, 1.0f},
        {0.6f, 0.0f, 0.7f, 1.0f},
        {0.7f, 0.0f, 0.8f, 1.0f},
        {0.8f, 0.0f, 0.9f, 1.0f},
        {0.9f, 0.0f, 1.0f, 1.0f}
    };

    //  UV作成
    initialize(
        digit, 
        tex,
        size,
        uv[0],
        uv[1],
        uv[2],
        uv[3],
        uv[4],
        uv[5],
        uv[6],
        uv[7],
        uv[8],
        uv[9]
    );
}

///
/// 初期化
void Numbers::initialize(
    int digit,                  //< 桁数
    const TexturePtr& tex,      //< テクスチャ
    const Vec2& size,           //< サイズ
    const TextureUV& uv0,       //< UV
    const TextureUV& uv1,       //< UV
    const TextureUV& uv2,       //< UV
    const TextureUV& uv3,       //< UV
    const TextureUV& uv4,       //< UV
    const TextureUV& uv5,       //< UV
    const TextureUV& uv6,       //< UV
    const TextureUV& uv7,       //< UV
    const TextureUV& uv8,       //< UV
    const TextureUV& uv9        //< UV
) {

    //  指定桁分の数字オブジェクト用意
    for (int i = 0; i < digit; ++i) {
        Number n;
        n.initialize(
            tex, 
            uv0, 
            uv1, 
            uv2, 
            uv3, 
            uv4,
            uv5, 
            uv6, 
            uv7, 
            uv8, 
            uv9
        );
    
        numbers_.push_back(n);
    }

    //  位置計算
    transform_ = Transform2D::create();

    //  相対関係構築
    for (auto& n : numbers_) {
        n.sprite()->size(size);
        n.sprite()->transform()->parent(transform_);
    }

    //  とりあえず中央寄せ
    alignCenter();
}

///
/// 中央寄せする
void Numbers::alignCenter() {
    size_t digit = numbers_.size();
    float sprite_width = numbers_.at(0).sprite()->size().x_;
    float start_x = sprite_width * digit * 0.5f;
    for (int i = 0; i < digit; ++i) {
        auto& n = numbers_.at(i);
        n.sprite()->transform()->position(start_x - (sprite_width * i), 0);
    }
}


TRI_JET_NS_END


