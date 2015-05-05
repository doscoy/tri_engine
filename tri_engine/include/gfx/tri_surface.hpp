#ifndef TRI_SURFACE_HPP_INCLUDED
#define TRI_SURFACE_HPP_INCLUDED


#include "gfx/tri_texture.hpp"

namespace t3 {


class Surface {

public:
    Surface();
    Surface(
        float width,
        float height
    );
    
    ~Surface();


public:
    TexturePtr texture() {
        return texture_;
    }
    
    const TexturePtr texture() const {
        return texture_;
    }
    
    float width() {
        return width_;
    }
    
    float height() {
        return height_;
    }
    
    void bind();
    void unbind();
    
    void clear();

private:
    float width_;
    float height_;
    cross::RenderSystem::FrameBufferID fb_;
    cross::RenderSystem::RenderBufferID cb_;
    cross::RenderSystem::RenderBufferID depth_;
    cross::RenderSystem::FrameBufferID last_fb_;
    cross::RenderSystem::RenderBufferID last_rb_;
    TexturePtr texture_;
};


}   // namespace t3


#endif  // TRI_SURFACE_HPP_INCLUDED
