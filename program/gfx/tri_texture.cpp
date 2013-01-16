
#include "tri_texture.hpp"
#include "tri_image_png.hpp"
#include "tri_texture_factory.hpp"


namespace t3 {
    
    
// *********************************************
//  コンストラクタ
Texture::Texture(
    const char* const name,
    const int width,
    const int height,
    const ColorFormat color_format,
    const byte* data
)   : size_( width, height )
    , color_format_( color_format )
    , data_( data )
{
    
        
}

std::shared_ptr<Texture> Texture::create( const char* const path )
{
    return TextureFactory::createFromFile( path );
}
    
    
}   // namespace t3
