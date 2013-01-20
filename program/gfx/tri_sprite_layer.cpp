
#include "tri_sprite_layer.hpp"

namespace t3 {
inline namespace gfx {
    
SpriteLayer::SpriteLayer()
    : RenderLayer( "Sprite" )
{
    
}

SpriteLayer::~SpriteLayer()
{
    
}


Sprite* SpriteLayer::createSprite( std::shared_ptr<Texture> tex )
{
    Sprite* spr( new Sprite );
    spr->setTexture( tex );
    spr->attachLayer( this );
    
    return spr;
}

void SpriteLayer::updateLayer( tick_t tick )
{
    for ( auto sp : sprites_ ){
        if ( !sp->isEnable() ) {
            continue;
        }
    }
}

void SpriteLayer::drawLayer()
{
    for ( auto sp : sprites_ ){
        if ( !sp->isEnable() ) {
            continue;
        }
        renderer_.collectSprite( *sp );
    }
    renderer_.render();
}


void SpriteLayer::attachSprite( Sprite* const sprite )
{
    sprites_.push_back( sprite );
}

void SpriteLayer::detachSprite( Sprite* const sprite )
{
    sprites_.remove( sprite );
    
}


}   // inline namespace gfx
}   // namespace t3

