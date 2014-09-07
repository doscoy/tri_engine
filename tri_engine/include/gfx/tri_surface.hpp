#ifndef TRI_SURFACE_HPP_INCLUDED
#define TRI_SURFACE_HPP_INCLUDED


#include "gfx/tri_texture.hpp"

namespace t3 {
inline namespace gfx {

class Surface {

public:
    Surface(
        int width,
        int height
    );
    
    ~Surface();


public:
    t3::TexturePtr texture() {
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

private:
    int width_;
    int height_;
    RenderSystem::FrameBufferID fb_;
    RenderSystem::RenderBufferID cb_;
    RenderSystem::RenderBufferID depth_;
    RenderSystem::FrameBufferID last_fb_;
    RenderSystem::RenderBufferID last_rb_;
    t3::TexturePtr texture_;
};


}   // namespace gfx
}   // namespace t3


#endif  // TRI_SURFACE_HPP_INCLUDED
