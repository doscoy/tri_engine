
#include "tri_texture.hpp"
#include "tri_image_png.hpp"
#include "tri_texture_factory.hpp"


namespace t3 {
inline namespace gfx {
    
// *********************************************
//  コンストラクタ
Texture::Texture(
    std::string name,
    const uint32_t width,
    const uint32_t height,
    const RenderSystem::ColorFormat color_format,
    const texture_handle_t tex_handle
)   : width_(width)
    , height_(height)
    , color_format_( color_format )
    , texture_handle_(tex_handle)
{
    
        
}

std::shared_ptr<Texture> Texture::create(FilePath& path)
{
    return TextureFactory::createFromFile(path);
}


void Texture::setupTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture_handle_);
    T3_ASSERT(glGetError() == GL_NO_ERROR);
}


}   // inline namespace gfx
}   // namespace t3
