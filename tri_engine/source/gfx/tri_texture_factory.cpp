
#include "tri_texture_factory.hpp"
#include "tri_texture.hpp"
#include "tri_image_png.hpp"
#include "dbg/tri_dbg.hpp"
#include "platform/platform_sdk.hpp"

namespace t3 {
inline namespace gfx {


std::shared_ptr<Texture> TextureFactory::createFromData(
    const char* const name,
    const uint32_t width,
    const uint32_t height,
    const RenderSystem::ColorFormat color_format,
    const void* data
) {
    
    texture_handle_t tex_handle;
    glGenTextures(1, &tex_handle);
    T3_ASSERT(glGetError() == GL_NO_ERROR);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    T3_ASSERT(glGetError() == GL_NO_ERROR);


    RenderSystem::setupTextureData(width, height, color_format, data);
    t3::RenderSystem::setTextureMinFilter(
        t3::RenderSystem::TextureFilterType::TYPE_NEAREST
    );
    t3::RenderSystem::setTextureMagFilter(
        t3::RenderSystem::TextureFilterType::TYPE_NEAREST
    );

    T3_ASSERT(glGetError() == GL_NO_ERROR);

    std::shared_ptr<Texture> tex( T3_NEW ::t3::Texture(
        name,
        width,
        height,
        color_format,
        tex_handle
    ));
    return tex;
}


// *********************************************
//  ファイルからテクスチャ生成
std::shared_ptr<Texture> TextureFactory::createFromFile(
    const char *const filename
){
    T3_TRACE( "Create texture from %s", filename );

    std::shared_ptr<Texture> tex = nullptr;
    int i = 1;
    while( filename[i] ){
        if ( filename[i] == '.' ){
            switch (filename[i+1]) {
                case 'p':
                    tex = createFromPng(filename);
                    break;
                    
                default:
                    T3_TRACE(" unknown texture type.");
                    break;
            }
        }
        ++i;
    }
    
    return tex;
}

// *********************************************
//  pngからテクスチャ生成
std::shared_ptr<Texture> TextureFactory::createFromPng(
    const char* const filename
){
    PngImage png( filename );
    RenderSystem::ColorFormat color_format = RenderSystem::ColorFormat::RGB;
    switch (png.color_type_) {
        
    case PNG_COLOR_TYPE_RGB:
        color_format = RenderSystem::ColorFormat::RGB;
        break;
    
    case PNG_COLOR_TYPE_RGBA:
        color_format = RenderSystem::ColorFormat::RGBA;
        break;
    
    default:
        T3_PANIC( "unknown color format." );
        break;
    }
    
    std::shared_ptr<Texture> tex = createFromData(
        filename,
        png.width_,
        png.height_,
        color_format,
        png.data_
    );
    
    return tex;
}


}   // namespace gfx
}   // namespace t3

