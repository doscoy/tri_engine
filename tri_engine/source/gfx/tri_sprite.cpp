
#include "tri_sprite.hpp"
#include "base/tri_game_system.hpp"
#include "gfx/tri_texture.hpp"
#include "gfx/tri_sprite_layer.hpp"
#include "gfx/tri_vertex_types.hpp"




namespace t3 {
inline namespace gfx {

//  コンストラクタ
Sprite::Sprite()
    : texture_(nullptr)
    , position_(0, 0)
    , size_(0, 0)
    , pivot_(0, 0)
    , rotation_(0.0f)
    , texture_coord_{0, 0, 1, 1}
    , scale_(1.0f, 1.0f)
    , priority_(PRIORITY_NORMAL)
    , enable_(true)
    , owner_(nullptr)
{
}

//  デストラクタ
Sprite::~Sprite()
{
}


//  テクスチャ設定
void Sprite::setTexture(
    std::shared_ptr<Texture> tex
){
    texture_ = tex;
    T3_NULL_ASSERT( texture_ );
    
    
    float tex_width = tex->getWidth();
    float tex_height = tex->getHeight();
    
    setSize(Vec2(tex_width, tex_height));
    setPivotByCenter();
}
  
bool Sprite::isValid() const
{
    if (!owner_) {
        return false;
    }
    

    return true;
}

int Sprite::getSortScore() const {
    int score = getPriority();
    return score;
}


void Sprite::setTextureCoordAndSizeByST(
    const Vec2& left_top,
    const Vec2& size
) {
    T3_NULL_ASSERT(texture_);
    
    float tex_width = texture_->getWidth();
    float tex_height = texture_->getHeight();
    
    float u0 = left_top.x_ / tex_width;
    float v0 = left_top.y_ / tex_height;
    float u1 = (left_top.x_ + size.x_) / tex_width;
    float v1 = (left_top.y_ + size.y_) / tex_height;
    
    setTextureCoord(u0, v0, u1, v1);
    setSize(size);
    setPivotByCenter();
}


void Sprite::setPivotByCenter() {
    setPivot(size_.x_ * 0.5f, size_.y_ * 0.5f);
}




}   // inline namespace gfx
}   // namespace t3

