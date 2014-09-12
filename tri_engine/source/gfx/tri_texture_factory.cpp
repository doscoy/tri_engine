
#include "gfx/tri_texture_factory.hpp"
#include "gfx/tri_texture.hpp"
#include "gfx/tri_image_png.hpp"
#include "dbg/tri_dbg.hpp"
#include "platform/platform_sdk.hpp"

namespace t3 {
inline namespace gfx {


TexturePtr TextureFactory::createFromData(
    std::string name,
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
    tex->resourceName(name.c_str());
    
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
    T3_TRACE("Create texture from %s", filename.getFullPath().c_str());

    TexturePtr tex = nullptr;
    std::string file_ext = filename.getExt();
    if (file_ext == ".png") {
        tex = createFromPngFile(filename);
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


    PngImage png(png_file);
    
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
    
    TexturePtr tex = createFromData(
        filepath.getFullPath(),
        png.width_,
        png.height_,
        color_format,
        png.data_
    );
    
    return tex;
}


}   // namespace gfx
}   // namespace t3

