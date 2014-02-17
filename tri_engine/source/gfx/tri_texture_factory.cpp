
#include "tri_texture_factory.hpp"
#include "tri_texture.hpp"
#include "tri_image_png.hpp"
#include "dbg/tri_dbg.hpp"


namespace t3 {
inline namespace gfx {


std::shared_ptr<Texture> TextureFactory::createFromData(
    const char* const name,
    const uint32_t width,
    const uint32_t height,
    const RenderSystem::ColorFormat color_format,
    const void* data
) {
    T3_NULL_ASSERT(data);
    std::shared_ptr<Texture> tex( T3_NEW ::t3::Texture(
        name,
        width,
        height,
        color_format,
        reinterpret_cast<const uint8_t*>(data)
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

