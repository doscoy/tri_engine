
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
    typedef std::list<std::shared_ptr<Sprite>> container_t;

public:
    SpriteLayer();
    virtual ~SpriteLayer();

public:
    std::shared_ptr<Sprite> createSprite(std::shared_ptr<Texture> tex);

    std::list<std::shared_ptr<Sprite>>* getManagementSprites() {
        return &sprites_;
    }
private:
    void updateLayer(tick_t delta_time) override;
    void drawLayer() override;
    void attachSprite(std::shared_ptr<Sprite> const sprite );
    void detachSprite(std::shared_ptr<Sprite> const sprite );

private:
    SpriteRenderer renderer_;
    container_t sprites_;
};

}   // namespace gfx
}   // namespace t3



#endif // TRI_SPRITE_LAYER


