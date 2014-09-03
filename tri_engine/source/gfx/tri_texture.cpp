
#include "gfx/tri_texture.hpp"
#include "gfx/tri_image_png.hpp"
#include "gfx/tri_texture_factory.hpp"


namespace t3 {
inline namespace gfx {
    
// *********************************************
//  コンストラクタ
Texture::Texture(
    std::string name,
    const uint32_t width,
    const uint32_t height,
    const RenderSystem::ColorFormat color_format,
    const RenderSystem::TextureID tex_handle
)   : Resource()
    , width_(width)
    , height_(height)
    , color_format_(color_format)
    , texture_handle_(tex_handle)
{
    
        
}

TexturePtr Texture::create(const FilePath& path) {
    return TextureFactory::createFromFile(path);
}


void Texture::bind() {

    RenderSystem::bindTexture(texture_handle_);
}


}   // inline namespace gfx
}   // namespace t3
