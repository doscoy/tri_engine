////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/tri_sprite_layer.hpp"
#include "core/graphics/tri_texture.hpp"


TRI_CORE_NS_BEGIN



SpriteLayer::SpriteLayer()
    : SpriteLayer("Sprite", 2048, PRIORITY_APP_DEFAULT)
{
}

SpriteLayer::SpriteLayer(
    const String& name,
    const int managed_size,
    const int priority
    ) : LayerBase(name, priority)
    , renderer_()
    , sprites_()
{
    for (int i = 0; i < managed_size; ++i) {
        sprites_.push_back(T3_SYS_NEW Sprite());
    }
}

SpriteLayer::~SpriteLayer() {
    for (int i = 0; i < sprites_.size(); ++i) {
        T3_DELETE sprites_[i];
    }
}

SpritePtr SpriteLayer::newSprite() {
    for (int i = 0; i < sprites_.size(); ++i) {
        SpritePtr spr = sprites_.at(i);
        if (!spr->isEnabled()) {
            return spr;
        }
    }

    return nullptr;
}

SpritePtr SpriteLayer::createSprite(TexturePtr tex) {
    SpritePtr spr = newSprite();
    if (spr) {
        spr->enable();
        spr->texture(tex);
    }


    return spr;
}


SpritePtr SpriteLayer::createSprite(const String& tex_name) {
    t3::TextureManager& tex_mgr = t3::TextureManager::instance();
    UniqueID tex_id = tex_mgr.load(tex_name);
    TexturePtr tex = tex_mgr.findResource(tex_id);

    return createSprite(tex);
}


void SpriteLayer::updateLayer(
    DeltaTime delta_time
    ) {
    //  レンダリング用にスプライトをマージする
    for (auto& sp : sprites_) {

        //  無効なスプライトはスキップ
        if (!sp->isEnabled()) {
            continue;
        }

        //  非表示のスプライトはスキップ
        if (!sp->isVisible()) {
            continue;
        }


        renderer_.collectSprite(sp);
    }

    //  スプライトがあれば、ドローコールを抑える為マージする
    if (!renderer_.collections().empty()) {
        renderer_.margeSprites();    
    }
    
}

void SpriteLayer::drawLayer() {

    if (renderer_.collections().empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }

    renderer_.render();
}


void SpriteLayer::disableAllSprites() {

    for (int i = 0; i < sprites_.size(); ++i) {
        sprites_[i]->destroy();
    }
}


TRI_CORE_NS_END

