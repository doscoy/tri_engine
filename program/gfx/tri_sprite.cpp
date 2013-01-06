
#include "tri_sprite.hpp"
#include <OpenGL/gl.h>
#include "../kernel/tri_game_system.hpp"
#include "../gfx/tri_resource_manager.hpp"






namespace t3 {


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
    , priority_( SPRITE_RENDER_PRIORITY_DEFAULT )
    , enable_( true )
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
    const t3::Texture& tex
){
    texture_ = &tex;
    size_ = tex.getSize();
    pivot_.x = size_.x * 0.5f;
    pivot_.y = size_.y * 0.5f;
}







}   // namespace t3

