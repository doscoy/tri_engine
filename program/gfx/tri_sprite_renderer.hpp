#ifndef TRI_SPRITE_RENDERER_HPP_INCLUDED
#define TRI_SPRITE_RENDERER_HPP_INCLUDED

#include "../util/tri_uncopyable.hpp"
#include "tri_vertex_buffer.hpp"
#include <vector>
#include <memory.h>

namespace t3 {
inline namespace gfx {

class IndexBuffer;
class Sprite;
class SpriteRenderer
    : private Uncopyable
{
    typedef std::vector<const Sprite*>      container_t;

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
    
    std::unique_ptr<VertexBuffer<VertexP2CT>> vertex_buffer_;
    std::unique_ptr<IndexBuffer> index_buffer_;

};


extern SpriteRenderer* renderer_;

}   // inline namespace gfx
}   // namespace t3




#endif // TRI_SPRITE_RENDERER_HPP_INCLUDED