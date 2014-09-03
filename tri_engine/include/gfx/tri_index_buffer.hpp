
#ifndef TRI_INDEX_BUFFER_HPP_INCLUDED
#define TRI_INDEX_BUFFER_HPP_INCLUDED

#include "tri_render_system.hpp"

namespace t3 {
inline namespace gfx {

class IndexBuffer {
public:
    IndexBuffer()
        : buffer_id_()
    {
        RenderSystem::createBuffer(&buffer_id_);
    }
    
    ~IndexBuffer() {
        RenderSystem::deleteBuffer(&buffer_id_);
    }
    
public:
    void bind() const {
        RenderSystem::bindBuffer(RenderSystem::BufferType::TYPE_INDEX, buffer_id_);
    }

private:
    RenderSystem::BufferID buffer_id_;
};

}   // namespace gfx
}   // namespace t3


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
