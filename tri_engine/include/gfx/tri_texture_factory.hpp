


#ifndef TRI_TEXTURE_FACTORY_HPP_INCLUDED
#define TRI_TEXTURE_FACTORY_HPP_INCLUDED

#include <memory>
#include "tri_render_system.hpp"
#include "kernel/io/tri_filepath.hpp"



namespace t3 {
inline namespace gfx {

class Texture;
class TextureFactory
{
public:
    static std::shared_ptr<Texture> createFromFile(
        FilePath& filename
    );

    
    static std::shared_ptr<Texture> createFromData(
        std::string name,
        const uint32_t width,
        const uint32_t height,
        const RenderSystem::ColorFormat color_format,
        const void* data
    );
    
private:
    static std::shared_ptr<Texture> createFromPngFile(
        FilePath& filepath
    );
};



}   // inline namespace gfx
}   // namespace t3

#endif // TRI_TEXTURE_FACTORY_HPP_INCLUDED

