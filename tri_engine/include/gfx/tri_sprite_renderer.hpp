#ifndef TRI_SPRITE_RENDERER_HPP_INCLUDED
#define TRI_SPRITE_RENDERER_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "tri_render_system.hpp"
#include <vector>
#include <memory.h>
#include "tri_shader.hpp"
#include "tri_sprite.hpp"


namespace t3 {
inline namespace gfx {

class IndexBuffer;
class SpriteRenderer
    : private Uncopyable
{
    using Container = std::vector<SpritePtr>;

public:
    SpriteRenderer();
    ~SpriteRenderer();
    
    
public:
    void collectSprite(SpritePtr sprite);
    void render();
    
    void useDefaultShader() {
        shader_ = default_shader_;
    }
    
    void useCustomShader(ShaderPtr shader) {
        shader_ = shader;
    }

private:
    void beginRender();
    void endRender();


    void margeSprites();
    void renderSprites();

private:
    Container sprites_;
    ShaderPtr shader_;
    ShaderPtr default_shader_;

    RenderSystem::BufferID vertex_buffer_;
    RenderSystem::BufferID index_buffer_;
    int draw_count_;
};


extern SpriteRenderer* renderer_;

}   // inline namespace gfx
}   // namespace t3




#endif // TRI_SPRITE_RENDERER_HPP_INCLUDED