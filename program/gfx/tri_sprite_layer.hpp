
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
    typedef std::list<Sprite*> container_t;
    friend void Sprite::attachToLayer( SpriteLayer* const layer );
    friend void Sprite::detachToLayer();
    
public:
    SpriteLayer();
    virtual ~SpriteLayer();

public:
    Sprite* createSprite( std::shared_ptr<Texture> tex );

private:
    virtual void updateLayer( tick_t tick ) override;
    virtual void drawLayer() override;
    void attachSprite( Sprite* const sprite );
    void detachSprite( Sprite* const sprite );

private:
    SpriteRenderer renderer_;
    container_t sprites_;
};

}   // namespace gfx
}   // namespace t3



#endif // TRI_SPRITE_LAYER


