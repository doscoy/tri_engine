
#ifndef TRI_VERTEX_BUFFER_HPP_INCLUDED
#define TRI_VERTEX_BUFFER_HPP_INCLUDED


#include "util/tri_uncopyable.hpp"



namespace t3 {
inline namespace gfx {

class VertexBuffer
    : Uncopyable {
public:
    VertexBuffer()
        : buffer_id_()
    {
        cross::RenderSystem::createBuffer(&buffer_id_);
    }
    
    ~VertexBuffer() {
        cross::RenderSystem::deleteBuffer(&buffer_id_);
    }
    
public:
    void bind() const {
        cross::RenderSystem::bindBuffer(cross::RenderSystem::BufferType::TYPE_VERTEX, buffer_id_);
    }

private:
    cross::RenderSystem::BufferID buffer_id_;
};

}   // namespace gfx
}   // namespace t3


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
