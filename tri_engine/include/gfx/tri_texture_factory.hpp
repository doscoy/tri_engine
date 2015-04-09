


#ifndef TRI_TEXTURE_FACTORY_HPP_INCLUDED
#define TRI_TEXTURE_FACTORY_HPP_INCLUDED

#include "base/tri_std.hpp"

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

    static TexturePtr createFromFile(
        const File& file
    );
    
    static TexturePtr createFromData(
        String name,
        const uint32_t width,
        const uint32_t height,
        const cross::RenderSystem::ColorFormat color_format,
        const void* data
    );
    
    static TexturePtr createFromPngFile(
        const FilePath& filepath
    );

    static TexturePtr createFromPngFile(
        const File& file
    );
};



}   // inline namespace gfx
}   // namespace t3

#endif // TRI_TEXTURE_FACTORY_HPP_INCLUDED

