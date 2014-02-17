


#ifndef TRI_TEXTURE_FACTORY_HPP_INCLUDED
#define TRI_TEXTURE_FACTORY_HPP_INCLUDED

#include <memory>
#include "tri_render_system.hpp"

namespace t3 {
inline namespace gfx {

class Texture;
class TextureFactory
{
public:
    static std::shared_ptr<Texture> createFromFile(
        const char* const filename
    );
    
    static std::shared_ptr<Texture> createFromData(
        const char* const name,
        const uint32_t width,
        const uint32_t height,
        const RenderSystem::ColorFormat color_format,
        const void* data
    );
    
private:
    static std::shared_ptr<Texture> createFromPng(
        const char* const png
    );
};



}   // inline namespace gfx
}   // namespace t3

#endif // TRI_TEXTURE_FACTORY_HPP_INCLUDED

