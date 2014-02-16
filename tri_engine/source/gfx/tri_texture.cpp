
#include "tri_texture.hpp"
#include "tri_image_png.hpp"
#include "tri_texture_factory.hpp"


namespace t3 {
inline namespace gfx {
    
// *********************************************
//  コンストラクタ
Texture::Texture(
    const char* const name,
    const int width,
    const int height,
    const RenderSystem::ColorFormat color_format,
    const int8_t* data
)   : size_( width, height )
    , color_format_( color_format )
    , data_( data )
{
    
        
}

std::shared_ptr<Texture> Texture::create( const char* const path )
{
    return TextureFactory::createFromFile( path );
}
    
}   // inline namespace gfx
}   // namespace t3
