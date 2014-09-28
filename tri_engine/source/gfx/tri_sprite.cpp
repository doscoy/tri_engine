
#include "gfx/tri_sprite.hpp"
#include "base/tri_director.hpp"
#include "gfx/tri_texture.hpp"
#include "gfx/tri_sprite_layer.hpp"
#include "gfx/tri_vertex_types.hpp"




namespace t3 {
inline namespace gfx {

//  コンストラクタ
Sprite::Sprite()
    : texture_(nullptr)
    , transform_(nullptr)
    , size_(0, 0)
    , pivot_(0, 0)
    , color_(255,255,255,255)
    , blend_mode_(RenderSystem::BlendMode::NORMAL)
    , texture_coord_{0, 0, 1, 1}
    , priority_(PRIORITY_NORMAL)
    , sort_score_(0)
    , enable_(true)
{
    calcSortScore();
    transform_ = std::make_shared<Transform2D>();
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
    
    
    float tex_width = tex->width();
    float tex_height = tex->height();
    
    size(Vec2(tex_width, tex_height));
    adjustPivotByCenter();
}
  

void Sprite::calcSortScore() {
    sort_score_ = priority() * 100;
    int blend_score = 0;
    if (blend_mode_ == RenderSystem::BlendMode::ADD) {
        blend_score = 10;
    }
    else if (blend_mode_ == RenderSystem::BlendMode::NONE){
        blend_score = 20;
    }
    sort_score_ += blend_score;
}

int Sprite::sortScore() const {
    return sort_score_;
}


void Sprite::textureCoord(
    const Vec2& left_top,
    const Vec2& size
) {
    T3_NULL_ASSERT(texture_);
    
    float tex_width = texture_->width();
    float tex_height = texture_->height();
    
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




}   // inline namespace gfx
}   // namespace t3

