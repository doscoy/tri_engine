////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/tri_texture_factory.hpp"
#include "core/graphics/tri_texture.hpp"
#include "core/graphics/tri_image_png.hpp"
#include "core/debug/tri_dbg.hpp"


#include "../../third_party/libpng/png.h"

TRI_CORE_NS_BEGIN




TexturePtr TextureFactory::createFromData(
    String name,
    const uint32_t width,
    const uint32_t height,
    const cross::RenderSystem::ColorFormat color_format,
    const cross::RenderSystem::TypeFormat type_format,
    const void* data
) {
    
    TexturePtr tex( T3_SYS_NEW ::t3::Texture(
        name.c_str(),
        width,
        height,
        color_format,
        type_format,
        nullptr
    ));

    cross::RenderSystem::bindTexture(tex->id());
    cross::RenderSystem::setupTextureData(
        width, 
        height, 
        color_format, 
        type_format, 
        data
    );
    cross::RenderSystem::setTextureMinFilter(
        cross::RenderSystem::TextureFilterType::TYPE_LINEAR
    );
    
    cross::RenderSystem::setTextureMagFilter(
        cross::RenderSystem::TextureFilterType::TYPE_LINEAR
    );


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
        T3_SYSTEM_WARNING("unknown texture type.");
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
    
    cross::RenderSystem::ColorFormat color_format = cross::RenderSystem::ColorFormat::RGB;
    switch (png.color_type_) {
        
    case PNG_COLOR_TYPE_RGB:
        color_format = cross::RenderSystem::ColorFormat::RGB;
        break;
    
    case PNG_COLOR_TYPE_RGBA:
        color_format = cross::RenderSystem::ColorFormat::RGBA;
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
        cross::RenderSystem::TypeFormat::UNSIGNED_BYTE,
        png.data_
    );
    
    return tex;
}


TRI_CORE_NS_END

