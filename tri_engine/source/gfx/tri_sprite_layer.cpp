
#include "gfx/tri_sprite_layer.hpp"
#include "gfx/tri_texture.hpp"


namespace t3 {
inline namespace gfx {
    
SpriteLayer::SpriteLayer()
    : SpriteLayer("Sprite", PRIORITY_APP_NORMAL)
{
}

SpriteLayer::SpriteLayer(
    const std::string& name,
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
    SpritePtr spr;
    spr.reset(T3_NEW Sprite);
    spr->texture(tex);
    attachSprite(spr);
    
    return spr;
}


SpritePtr SpriteLayer::createSprite(const t3::FilePath& path) {
    t3::TextureManager& tex_mgr = t3::TextureManager::instance();
    UniqueID tex_id = tex_mgr.load(path);
    std::shared_ptr<t3::Texture> tex = tex_mgr.resource(tex_id);
    return createSprite(tex);
}


void SpriteLayer::updateLayer(
    tick_t delta_time
) {
    if (sprites_.empty()) {
        //  スプライト無ければ処理スキップ
        return;
    }

    //  無効になった要素の掃除
    sprites_.remove_if([](WeakSprite& wk){return wk.expired();});


    //  レンダリング用にスプライトをマージする
    for (auto target : sprites_) {
        //  対象のポインタは無効
        if (target.expired()) {
            T3_PANIC("null sprite.");
            continue;
        }
        
        auto sp = target.lock();
    
        if (!sp->enabled()) {
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



}   // inline namespace gfx
}   // namespace t3

