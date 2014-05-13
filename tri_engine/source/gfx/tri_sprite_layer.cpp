
#include "tri_sprite_layer.hpp"
#include "tri_texture.hpp"


namespace t3 {
inline namespace gfx {
    
SpriteLayer::SpriteLayer()
    : RenderLayer("Sprite")
{
    
}

SpriteLayer::~SpriteLayer()
{
    detachAllSprite();

    sprites_.clear();
}


SpritePtr SpriteLayer::createSprite(std::shared_ptr<Texture> tex) {
    SpritePtr spr;
    spr.reset(new Sprite);
    spr->setTexture(tex);
    attachSprite(spr);
    
    return spr;
}


SpritePtr SpriteLayer::createSprite(const t3::FilePath& path) {
    t3::TextureManager& tex_mgr = t3::TextureManager::getInstance();
    UniqueID tex_id = tex_mgr.load(path);
    std::shared_ptr<t3::Texture> tex = tex_mgr.getResource(tex_id);
    return createSprite(tex);
}


void SpriteLayer::updateLayer(
    tick_t delta_time
) {
    if (sprites_.empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }

    for (auto sp : sprites_) {
        if (!sp->isEnable()) {
            continue;
        }
        renderer_.collectSprite(sp);
    }
}

void SpriteLayer::drawLayer() {
    if (sprites_.empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }
    
    for (auto sp : sprites_) {
        if (!sp->isEnable()) {
            continue;
        }
    }

    renderer_.render();
    
}


void SpriteLayer::attachSprite(SpritePtr const sprite) {
    sprites_.push_back(sprite);
    sprite->setAttachedLayer(this);
}

void SpriteLayer::detachSprite(SpritePtr const sprite) {
    sprites_.remove(sprite);
    sprite->setAttachedLayer(nullptr);
}


void SpriteLayer::detachAllSprite() {
    container_t::iterator it = sprites_.begin();
    container_t::iterator end = sprites_.end();
    
    while (it != end) {
        (*it)->setAttachedLayer(nullptr);
        it = sprites_.erase(it);
    }
}



}   // inline namespace gfx
}   // namespace t3

