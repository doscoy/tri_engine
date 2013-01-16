#include "../tri_develop_base.hpp"

#include "tri_texture_factory.hpp"
#include "tri_texture.hpp"
#include "tri_image_png.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../../otherlib/libpng/png.h"


namespace t3 {


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
    ColorFormat color_format;
    switch (png.color_type_) {
        case PNG_COLOR_TYPE_RGB:
            color_format = RGB;
            break;
        case PNG_COLOR_TYPE_RGBA:
            color_format = RGBA;
            break;
        default:
            T3_PANIC( "unknown color format." );
            break;
    }
    
    std::shared_ptr<Texture> tex( T3_NEW ::t3::Texture(
        filename,
        png.width_,
        png.height_,
        color_format,
        (const byte*)png.data_
    ));
    return tex;
}



}   // namespace t3

