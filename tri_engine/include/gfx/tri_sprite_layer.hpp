
#ifndef TRI_SPRITE_LAYER_HPP_INCLUDED
#define TRI_SPRITE_LAYER_HPP_INCLUDED

#include "tri_render_layer.hpp"
#include "tri_sprite.hpp"
#include "tri_sprite_renderer.hpp"
#include <list>
#include <memory.h>

namespace t3 {


class SpriteLayer
    : public RenderLayer
{
public:
    
    using SpriteContainer = List<WeakSprite>;

public:
    SpriteLayer();
    SpriteLayer(
        const String& name,
        const int priority = PRIORITY_APP_DEFAULT
    );
    virtual ~SpriteLayer();

public:
    SpritePtr createSprite(TexturePtr tex);
    SpritePtr createSprite(const String& tex_name);

    SpriteContainer* getManagementSprites() {
        return &sprites_;
    }


    SpriteRenderer& renderer() {
        return renderer_;
    }
    
private:
    void attachSprite(WeakSprite const sprite);
    void detachAllSprite();

    void updateLayer(tick_t delta_time) override;
    void drawLayer() override;
    
private:
    SpriteRenderer renderer_;
    SpriteContainer sprites_;
    
};


}   // namespace t3



#endif // TRI_SPRITE_LAYER


