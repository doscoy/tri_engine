
#include "graphics/tri_sprite_layer.hpp"
#include "graphics/tri_texture.hpp"


TRI_CORE_NS_BEGIN


    
SpriteLayer::SpriteLayer()
    : SpriteLayer("Sprite", PRIORITY_APP_DEFAULT)
{
}

SpriteLayer::SpriteLayer(
    const String& name,
    const int priority
)   : RenderLayer(name, priority)
    , renderer_()
    , sprites_()
{
}

SpriteLayer::~SpriteLayer()
{
    detachAllSprite();

    sprites_.clear();
}


SpritePtr SpriteLayer::createSprite(TexturePtr tex) {
    SpritePtr spr(T3_SYS_NEW Sprite);
    spr->texture(tex);
    attachSprite(spr);
    
    return spr;
}


SpritePtr SpriteLayer::createSprite(const String& tex_name) {
    t3::TextureManager& tex_mgr = t3::TextureManager::instance();
    UniqueID tex_id = tex_mgr.load(tex_name);
    TexturePtr tex = tex_mgr.findResource(tex_id);
    
    return createSprite(tex);
}


void SpriteLayer::updateLayer(
    tick_t delta_time
) {
    //  無効になった要素の掃除
    sprites_.remove_if([](WeakSprite& wk){return wk.expired();});

    if (sprites_.empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }



    //  レンダリング用にスプライトをマージする
    for (auto& target : sprites_) {
        
        auto sp = target.lock();
    
        if (!sp->enabled()) {
            continue;
        }
        renderer_.collectSprite(sp);
    }
    
    renderer_.margeSprites();
    
}

void SpriteLayer::drawLayer() {

    if (sprites_.empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }

    renderer_.render();
}


void SpriteLayer::attachSprite(WeakSprite sprite) {
    sprites_.push_back(sprite);
}



void SpriteLayer::detachAllSprite() {
    SpriteContainer::iterator it = sprites_.begin();
    SpriteContainer::iterator end = sprites_.end();
    
    while (it != end) {
        it = sprites_.erase(it);
    }
}

TRI_CORE_NS_END

