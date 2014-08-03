
#include "tri_sprite.hpp"
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
    , texture_coord_{0, 0, 1, 1}
    , priority_(PRIORITY_NORMAL)
    , enable_(true)
    , owner_(nullptr)
{

    transform_ = std::make_shared<Transform2D>();
}

//  デストラクタ
Sprite::~Sprite()
{
}


//  テクスチャ設定
void Sprite::texture(
    std::shared_ptr<Texture> tex
){
    texture_ = tex;
    T3_NULL_ASSERT( texture_ );
    
    
    float tex_width = tex->width();
    float tex_height = tex->height();
    
    size(Vec2(tex_width, tex_height));
    adjustPivotByCenter();
}
  
bool Sprite::isValid() const
{
    if (!owner_) {
        return false;
    }
    

    return true;
}

int Sprite::sortScore() const {
    int score = priority();
    return score;
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

