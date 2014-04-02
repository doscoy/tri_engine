
#include "tri_sprite_layer.hpp"

namespace t3 {
inline namespace gfx {
    
SpriteLayer::SpriteLayer()
    : RenderLayer( "Sprite" )
{
    
}

SpriteLayer::~SpriteLayer()
{
    sprites_.clear();
}


std::shared_ptr<Sprite> SpriteLayer::createSprite(std::shared_ptr<Texture> tex) {
    std::shared_ptr<Sprite> spr;
    spr.reset(new Sprite);
    spr->setTexture(tex);
    attachSprite(spr);
    
    return spr;
}

void SpriteLayer::updateLayer( tick_t delta_time )
{
    if (sprites_.empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }

    for ( auto sp : sprites_ ){
        if ( !sp->isEnable() ) {
            continue;
        }
    }
}

void SpriteLayer::drawLayer()
{
    if (sprites_.empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }

    for ( auto sp : sprites_ ){
        if ( !sp->isEnable() ) {
            continue;
        }
        renderer_.collectSprite( *sp );
    }

    renderer_.render();
}


void SpriteLayer::attachSprite(std::shared_ptr<Sprite> const sprite) {
    sprites_.push_back(sprite);
}

void SpriteLayer::detachSprite(std::shared_ptr<Sprite> const sprite) {
    sprites_.remove(sprite);
}


}   // inline namespace gfx
}   // namespace t3

