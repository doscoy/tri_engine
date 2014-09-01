


#ifndef TRI_TEXTURE_FACTORY_HPP_INCLUDED
#define TRI_TEXTURE_FACTORY_HPP_INCLUDED

#include <memory>
#include "tri_render_system.hpp"
#include "kernel/io/tri_filepath.hpp"
#include "tri_texture.hpp"


namespace t3 {
inline namespace gfx {


class TextureFactory
{
public:
    static TexturePtr createFromFile(
        const FilePath& filename
    );

    
    static TexturePtr createFromData(
        std::string name,
        const uint32_t width,
        const uint32_t height,
        const RenderSystem::ColorFormat color_format,
        const void* data
    );
    
private:
    static TexturePtr createFromPngFile(
        const FilePath& filepath
    );
};



}   // inline namespace gfx
}   // namespace t3

#endif // TRI_TEXTURE_FACTORY_HPP_INCLUDED

