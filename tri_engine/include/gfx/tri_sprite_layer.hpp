
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
    typedef std::list<SpritePtr> container_t;

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

    std::list<SpritePtr>* getManagementSprites() {
        return &sprites_;
    }

    void detachSprite(SpritePtr const sprite);
    void detachAllSprite();
    
    
private:
    void updateLayer(tick_t delta_time) override;
    void drawLayer() override;
    void attachSprite(SpritePtr const sprite);
    
private:
    SpriteRenderer renderer_;
    container_t sprites_;
    
};

}   // namespace gfx
}   // namespace t3



#endif // TRI_SPRITE_LAYER


