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


private:
    int width_;
    int height_;
    uint32_t fb_;
    uint32_t depth_;
    t3::TexturePtr texture_;
};


}   // namespace gfx
}   // namespace t3


#endif  // TRI_SURFACE_HPP_INCLUDED
