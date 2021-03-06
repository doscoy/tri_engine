////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/tri_texture.hpp"
#include "core/graphics/tri_image_png.hpp"
#include "core/graphics/tri_texture_factory.hpp"


TRI_CORE_NS_BEGIN


    
// *********************************************
//  コンストラクタ
Texture::Texture(
    String name,
    const uint32_t width,
    const uint32_t height,
    const cross::RenderSystem::ColorFormat color_format,
    const cross::RenderSystem::TypeFormat type_format,
    uint8_t* data
)   : Resource()
    , width_(width)
    , height_(height)
    , color_format_(color_format)
    , type_format_(type_format)
    , texture_handle_(0)
{
    resourceName(name.c_str());
    texture_handle_ = cross::RenderSystem::createTexture();


    cross::RenderSystem::bindTexture(texture_handle_);
    
    cross::RenderSystem::setTextureWrap(cross::RenderSystem::TextureWrapType::CLAMP_TO_EDGE);
    cross::RenderSystem::setTextureMagFilter(cross::RenderSystem::TextureFilterType::TYPE_LINEAR);
    cross::RenderSystem::setTextureMinFilter(cross::RenderSystem::TextureFilterType::TYPE_LINEAR);
    cross::RenderSystem::setTextureCompareFunc(cross::RenderSystem::TextureCompareFunc::LESS);
    cross::RenderSystem::setTextureCompareMode(cross::RenderSystem::TextureCompareMode::REF_TO_TEX);

    cross::RenderSystem::setupTextureData(width, height, color_format, type_format, data);


    cross::RenderSystem::bindTexture(0);

}

Texture::~Texture() {
    cross::RenderSystem::deleteTexture(&texture_handle_);
}



TexturePtr Texture::create(const FilePath& path) {
    return TextureFactory::createFromFile(path);
}


TexturePtr Texture::create(
    String name,
    const uint32_t width,
    const uint32_t height,
    const cross::RenderSystem::ColorFormat color_format,
    const cross::RenderSystem::TypeFormat type_format,
    uint8_t* data
) {
    TexturePtr t(T3_SYS_NEW Texture(
        name,
        width,
        height,
        color_format,
        type_format,
        data
    ));
    
    return t;
}

TexturePtr Texture::create(const t3::File& file) {
    
    return TextureFactory::createFromFile(file);
}


void Texture::bind() {

    cross::RenderSystem::bindTexture(texture_handle_);
}


TRI_CORE_NS_END
