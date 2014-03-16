#ifndef TRI_SPRITE_RENDERER_HPP_INCLUDED
#define TRI_SPRITE_RENDERER_HPP_INCLUDED

#include "../util/tri_uncopyable.hpp"
#include "tri_render_system.hpp"
#include <vector>
#include <memory.h>
#include "tri_shader.hpp"



namespace t3 {
inline namespace gfx {

class IndexBuffer;
class Sprite;
class SpriteRenderer
    : private Uncopyable
{
    using Container = std::vector<Sprite*>;

public:
    SpriteRenderer();
    ~SpriteRenderer();
    
    
public:
    void collectSprite(Sprite& sprite);
    void render();
    

private:
    void beginRender();
    void renderSprite(Sprite& sprite);
    void endRender();

private:
    Container sprites_;


    Shader sprite_shader_;
};


extern SpriteRenderer* renderer_;

}   // inline namespace gfx
}   // namespace t3




#endif // TRI_SPRITE_RENDERER_HPP_INCLUDED