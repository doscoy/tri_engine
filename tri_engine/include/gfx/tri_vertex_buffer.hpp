
#ifndef TRI_VERTEX_BUFFER_HPP_INCLUDED
#define TRI_VERTEX_BUFFER_HPP_INCLUDED

#include "tri_render_system.hpp"
#include "util/tri_uncopyable.hpp"



namespace t3 {
inline namespace gfx {

class VertexBuffer
    : Uncopyable {
public:
    VertexBuffer()
        : buffer_id_()
    {
        RenderSystem::createBuffer(&buffer_id_);
    }
    
    ~VertexBuffer() {
        RenderSystem::deleteBuffer(&buffer_id_);
    }
    
public:
    void bind() const {
        RenderSystem::bindBuffer(RenderSystem::BufferType::TYPE_VERTEX, buffer_id_);
    }

private:
    RenderSystem::BufferID buffer_id_;
};

}   // namespace gfx
}   // namespace t3


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
