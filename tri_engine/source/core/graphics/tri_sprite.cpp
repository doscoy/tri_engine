////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/tri_sprite.hpp"
#include "core/base/tri_director.hpp"
#include "core/graphics/tri_texture.hpp"
#include "core/graphics/layer/tri_sprite_layer.hpp"
#include "core/graphics/tri_vertex_types.hpp"


TRI_CORE_NS_BEGIN



//  コンストラクタ
Sprite::Sprite()
    : texture_(nullptr)
    , transform_(nullptr)
    , size_(0, 0)
    , pivot_(0, 0)
    , color_(255,255,255,255)
    , blend_mode_(cross::RenderSystem::BlendMode::NORMAL)
    , priority_(PRIORITY_NORMAL)
    , sort_score_(0)
    , visibility_(true)
    , enable_(false)
{
    calcSortScore();
    transform_ = Transform2D::create();

	texture_coord_ = { 0,0,1,1 };
}

//  デストラクタ
Sprite::~Sprite()
{
}


//  テクスチャ設定
void Sprite::texture(
    TexturePtr tex
){
    texture_ = tex;
    T3_NULL_ASSERT( texture_ );
    
    
    float tex_width = static_cast<float>(tex->width());
    float tex_height = static_cast<float>(tex->height());
    
    size(Vec2(tex_width, tex_height));
    adjustPivotByCenter();
}
  

///
/// ソート時のキーとなるスコア計算
void Sprite::calcSortScore() {
    int score = priority() * 100;

    //  ブレンドモードによって描画グループを分ける為にスコアを変える
    constexpr int BLEND_SCORE_MODE_NORMAL = 0;
    constexpr int BLEND_SCORE_MODE_ADD = 20;
    constexpr int BLEND_SCORE_MODE_NONE = 40;
    int blend_score = BLEND_SCORE_MODE_NORMAL;
    if (blend_mode_ == cross::RenderSystem::BlendMode::ADD) {
        //  加算半透明
        blend_score = BLEND_SCORE_MODE_ADD;
    }
    else if (blend_mode_ == cross::RenderSystem::BlendMode::NONE){
        //  ブレンド無し
        blend_score = BLEND_SCORE_MODE_NONE;
    }
    
    //  スプライトのプライオリティとブレンドモードのスコアから最終的なスコアを求める
    score += blend_score;
 
    //  計算結果を設定
    sort_score_ = score;
}



void Sprite::textureCoord(
    const Vec2& left_top,
    const Vec2& size
) {
    T3_NULL_ASSERT(texture_);
    
    float tex_width = static_cast<float>(texture_->width());
    float tex_height = static_cast<float>(texture_->height());
    
    float u0 = left_top.x_ / tex_width;
    float v0 = left_top.y_ / tex_height;
    float u1 = (left_top.x_ + size.x_) / tex_width;
    float v1 = (left_top.y_ + size.y_) / tex_height;
    
    textureCoord(u0, v0, u1, v1);
}


void Sprite::setupTextureCoordAndSize(
    const Vec2& left_top,
    const Vec2& st_size
) {
    textureCoord(left_top, st_size);
    size(st_size);
    adjustPivotByCenter();
}


void Sprite::adjustPivotByCenter() {
    pivot(size_.x_ * 0.5f, size_.y_ * 0.5f);
}

///
/// 生成
SpritePtr Sprite::create(
    String tex_name,
    String layer_name
) {
    //  お目当てのレイヤーを取得
    auto& director = Director::instance();
    LayerBase* layer = director.findLayer(layer_name);
    SpriteLayer* sprite_layer = dynamic_cast<SpriteLayer*>(layer);
    
    T3_NULL_ASSERT(sprite_layer);
    
    auto sprite = sprite_layer->createSprite(tex_name);
    return sprite;
}

///
/// 生成
SpritePtr Sprite::create(
    TexturePtr texture,
    String layer_name
) {
    //  お目当てのレイヤーを取得
    auto& director = Director::instance();
    LayerBase* layer = director.findLayer(layer_name);
    SpriteLayer* sprite_layer = dynamic_cast<SpriteLayer*>(layer);
    
    T3_NULL_ASSERT(sprite_layer);
    
    auto sprite = sprite_layer->createSprite(texture);
    return sprite;
}




TRI_CORE_NS_END

