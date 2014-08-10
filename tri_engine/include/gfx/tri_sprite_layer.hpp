
#ifndef TRI_SPRITE_LAYER_HPP_INCLUDED
#define TRI_SPRITE_LAYER_HPP_INCLUDED

#include "tri_render_layer.hpp"
#include "tri_sprite.hpp"
#include "tri_sprite_renderer.hpp"
#include <list>
#include <memory.h>

namespace t3 {
inline namespace gfx {


class SpriteLayer
    : public RenderLayer
{
public:
    
    using SpriteContainer = std::list<WeakSprite>;

public:
    SpriteLayer();
    SpriteLayer(
        const std::string& name,
        const int priority
    );
    virtual ~SpriteLayer();

public:
    SpritePtr createSprite(std::shared_ptr<Texture> tex);
    SpritePtr createSprite(const FilePath& path);

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

}   // namespace gfx
}   // namespace t3



#endif // TRI_SPRITE_LAYER


