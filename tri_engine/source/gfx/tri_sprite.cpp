
#include "tri_sprite.hpp"
#include "base/tri_game_system.hpp"
#include "gfx/tri_texture.hpp"
#include "gfx/tri_sprite_layer.hpp"
#include "gfx/tri_vertex_types.hpp"




namespace t3 {
inline namespace gfx {

// *********************************************
//  コンストラクタ
Sprite::Sprite()
    : texture_(nullptr)
    , position_(0, 0)
    , size_(0, 0)
    , pivot_(0, 0)
    , rotation_(0, 0, 0)
    , texture_coord_{0, 0, 1, 1}
    , scale_(1.0f, 1.0f)
    , priority_(PRIORITY_NORMAL)
    , enable_(true)
    , owner_(nullptr)
{
}


// *********************************************
//  デストラクタ
Sprite::~Sprite()
{
}


// *********************************************
//  テクスチャ設定
void Sprite::setTexture(
    std::shared_ptr<Texture> tex
){
    texture_ = tex;
    T3_NULL_ASSERT( texture_ );
    
    
    float tex_width = tex->getWidth();
    float tex_height = tex->getHeight();
    
    setPivot(Vec2(tex_width * 0.5f, tex_height * 0.5f));

    setSize(Vec2(tex_width, tex_height));
    
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







}   // inline namespace gfx
}   // namespace t3

