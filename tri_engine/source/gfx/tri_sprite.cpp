
#include "tri_sprite.hpp"
#include "base/tri_game_system.hpp"
#include "gfx/tri_resource_manager.hpp"
#include "tri_sprite_layer.hpp"





namespace t3 {
inline namespace gfx {

// *********************************************
//  コンストラクタ
Sprite::Sprite()
    : texture_( nullptr )
    , position_( 0, 0 )
    , size_( 0, 0 )
    , pivot_( 0, 0 )
    , rotation_( 0 )
    , texture_coord_{ 0, 0, 1, 1 }
    , scale_( 1.0f, 1.0f )
    , priority_( PRIORITY_NORMAL )
    , enable_( true )
    , owner_( nullptr )
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
    
    
    pivot_.x_ = tex->getWidth() * 0.5f;
    pivot_.y_ = tex->getHeight() * 0.5f;
}

void Sprite::attachToLayer( SpriteLayer* const layer )
{
    owner_ = layer;
    owner_->attachSprite( this );
}

void Sprite::detachToLayer()
{
    T3_NULL_ASSERT( owner_ );
    owner_->detachSprite( this );
    owner_ = nullptr;
}


void Sprite::destroy()
{
    detachToLayer();
    delete this;
}


bool Sprite::isValid() const
{
    if ( !owner_ ){
        return false;
    }
    

    return true;
}


}   // inline namespace gfx
}   // namespace t3

