
#ifndef TRI_INDEX_BUFFER_HPP_INCLUDED
#define TRI_INDEX_BUFFER_HPP_INCLUDED

#include <cross_sdk/cross_sdk.hpp>

namespace t3 {
inline namespace gfx {

class IndexBuffer {
public:
    IndexBuffer()
        : buffer_id_()
    {
        cross::RenderSystem::createBuffer(&buffer_id_);
    }
    
    ~IndexBuffer() {
        cross::RenderSystem::deleteBuffer(&buffer_id_);
    }
    
public:
    void bind() const {
        cross::RenderSystem::bindBuffer(cross::RenderSystem::BufferType::TYPE_INDEX, buffer_id_);
    }

private:
    cross::RenderSystem::BufferID buffer_id_;
};

}   // namespace gfx
}   // namespace t3


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
