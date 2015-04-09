#ifndef TRI_SURFACE_HPP_INCLUDED
#define TRI_SURFACE_HPP_INCLUDED


#include "gfx/tri_texture.hpp"

namespace t3 {
inline namespace gfx {

class Surface {

public:
    Surface();
    Surface(
        int width,
        int height
    );
    
    ~Surface();


public:
    TexturePtr texture() {
        return texture_;
    }
    
    const TexturePtr texture() const {
        return texture_;
    }
    
    int width() {
        return width_;
    }
    
    int height() {
        return height_;
    }
    
    void bind();
    void unbind();
    
    void clear();

private:
    int width_;
    int height_;
    cross::RenderSystem::FrameBufferID fb_;
    cross::RenderSystem::RenderBufferID cb_;
    cross::RenderSystem::RenderBufferID depth_;
    cross::RenderSystem::FrameBufferID last_fb_;
    cross::RenderSystem::RenderBufferID last_rb_;
    TexturePtr texture_;
};


}   // namespace gfx
}   // namespace t3


#endif  // TRI_SURFACE_HPP_INCLUDED
