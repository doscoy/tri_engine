#ifndef TRI_SPRITE_RENDERER_HPP_INCLUDED
#define TRI_SPRITE_RENDERER_HPP_INCLUDED

#include "../util/tri_uncopyable.hpp"
#include "tri_render_system.hpp"
#include <vector>
#include <memory.h>




namespace t3 {
inline namespace gfx {

class IndexBuffer;
class Sprite;
class SpriteRenderer
    : private Uncopyable
{
    using container_t = std::vector<const Sprite*>;

public:
    SpriteRenderer();
    ~SpriteRenderer();
    
    
public:
    void collectSprite( const Sprite& sprite );    
    void render();
    

private:
    void beginRender();
    void endRender();

private:
    container_t sprites_;
    
    buffer_id_t vertex_buffer_;
    buffer_id_t index_buffer_;
    
    shader_program_t sprite_render_shader_;
    shader_variable_t sv_pos_;
    shader_variable_t sv_uv_;
    
};


extern SpriteRenderer* renderer_;

}   // inline namespace gfx
}   // namespace t3




#endif // TRI_SPRITE_RENDERER_HPP_INCLUDED