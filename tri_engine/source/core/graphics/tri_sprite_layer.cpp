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
    : SpriteLayer("Sprite")
{
}

SpriteLayer::SpriteLayer(
    const String& name,
    const Priority priority
) : LayerBase(name, priority)
    , renderer_()
    , sprites_()
{
}

SpriteLayer::~SpriteLayer() {

}

SpritePtr SpriteLayer::newSprite() {
    SpritePtr sprite(T3_NEW Sprite);
    sprites_.push_back(sprite);

    return sprite;
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
    const DeltaTime delta_time
) {

    renderer_.beginCollect();

    //  期限の切れたスプライトを削除
    sprites_.remove_if(
        [](SpriteWeakPtr p) {
            return p.expired();
        }
    );

    //  レンダリング用にスプライトをマージする
    for (auto& weak_sprite : sprites_) {

        //  もうスプライトが存在していない
        auto sp = weak_sprite.lock();
        if (!sp) {
            //  もうスプライトが存在していない
            continue;
        }
        
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
    if (renderer_.hasSprites()) {
        renderer_.margeSprites();
    }
    
}

void SpriteLayer::renderLayer() {

    if (!renderer_.hasSprites()) {
        //  スプライト無ければ処理スキップ
        return;
    }

    renderer_.render();
}





TRI_CORE_NS_END

