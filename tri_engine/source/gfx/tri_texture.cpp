
#include "gfx/tri_texture.hpp"
#include "gfx/tri_image_png.hpp"
#include "gfx/tri_texture_factory.hpp"


namespace t3 {
inline namespace gfx {
    
// *********************************************
//  コンストラクタ
Texture::Texture(
    String name,
    const uint32_t width,
    const uint32_t height,
    const RenderSystem::ColorFormat color_format
)   : Resource()
    , width_(width)
    , height_(height)
    , color_format_(color_format)
    , texture_handle_(0)
{
    resourceName(name.c_str());
    glGenTextures(1, &texture_handle_);
    T3_ASSERT(glGetError() == GL_NO_ERROR);
    glBindTexture(GL_TEXTURE_2D, texture_handle_);
    T3_ASSERT(glGetError() == GL_NO_ERROR);
    
    RenderSystem::setTextureWrap(t3::RenderSystem::TextureWrapType::TYPE_CLAMP_TO_EDGE);
    RenderSystem::setTextureMagFilter(t3::RenderSystem::TextureFilterType::TYPE_LINEAR);
    RenderSystem::setTextureMinFilter(t3::RenderSystem::TextureFilterType::TYPE_LINEAR);

    RenderSystem::setTextureMagFilter(RenderSystem::TextureFilterType::TYPE_LINEAR);
    RenderSystem::setTextureMinFilter(RenderSystem::TextureFilterType::TYPE_LINEAR);
    RenderSystem::setupTextureData(width, height, RenderSystem::ColorFormat::RGBA, nullptr);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture_handle_);
}



TexturePtr Texture::create(const FilePath& path) {
    return TextureFactory::createFromFile(path);
}


TexturePtr Texture::create(
    String name,
    const int width,
    const int height,
    const RenderSystem::ColorFormat color_format
) {
    TexturePtr t;
    t.reset(T3_SYS_NEW Texture(
        name,
        width,
        height,
        color_format
    ));
    
    return t;
}


void Texture::bind() {

    RenderSystem::bindTexture(texture_handle_);
}


}   // inline namespace gfx
}   // namespace t3
