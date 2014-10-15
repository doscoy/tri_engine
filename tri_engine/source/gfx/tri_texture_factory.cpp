
#include "gfx/tri_texture_factory.hpp"
#include "gfx/tri_texture.hpp"
#include "gfx/tri_image_png.hpp"
#include "dbg/tri_dbg.hpp"
#include "platform/platform_sdk.hpp"

namespace t3 {
inline namespace gfx {


TexturePtr TextureFactory::createFromData(
    String name,
    const uint32_t width,
    const uint32_t height,
    const RenderSystem::ColorFormat color_format,
    const void* data
) {
    
    TexturePtr tex( T3_SYS_NEW ::t3::Texture(
        name.c_str(),
        width,
        height,
        color_format
    ));
    
    glBindTexture(GL_TEXTURE_2D, tex->id());
    RenderSystem::setupTextureData(width, height, color_format, data);
    t3::RenderSystem::setTextureMinFilter(
        t3::RenderSystem::TextureFilterType::TYPE_NEAREST
    );
    
    t3::RenderSystem::setTextureMagFilter(
        t3::RenderSystem::TextureFilterType::TYPE_NEAREST
    );


    T3_ASSERT(glGetError() == GL_NO_ERROR);

    return tex;
}


//  ファイルからテクスチャ生成
TexturePtr TextureFactory::createFromFile(
    const FilePath& filename
){
    File file;
    file.loadFile(filename);

    return createFromFile(file);
}

TexturePtr TextureFactory::createFromFile(const t3::File& file) {
    TexturePtr tex = nullptr;
    FilePath path = file.name();
    String file_ext = path.ext();
    if (file_ext == ".png") {
        tex = createFromPngFile(file);
    }
    else {
        T3_TRACE("unknown texture type.");
    }

    return tex;
}


//  pngからテクスチャ生成
TexturePtr TextureFactory::createFromPngFile(
    const FilePath& filepath
){
    File png_file;
    png_file.loadFile(filepath);

    return createFromPngFile(png_file);
}

TexturePtr TextureFactory::createFromPngFile(const File& file) {

    PngImage png(file);
    
    RenderSystem::ColorFormat color_format = RenderSystem::ColorFormat::RGB;
    switch (png.color_type_) {
    case PNG_COLOR_TYPE_GRAY:
        color_format = RenderSystem::ColorFormat::GRAY;
        break;
        
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
    
    TexturePtr tex = createFromData(
        file.name(),
        png.width_,
        png.height_,
        color_format,
        png.data_
    );
    
    return tex;
}


}   // namespace gfx
}   // namespace t3

