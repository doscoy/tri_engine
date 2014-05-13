#ifndef TRI_TEXTURE_HPP_INCLUDED
#define TRI_TEXTURE_HPP_INCLUDED

#include "../util/tri_unique_id.hpp"
#include "../math/tri_vec2.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../base/tri_resource.hpp"
#include "../gfx/tri_color.hpp"
#include "gfx/tri_render_system.hpp"
#include "base/tri_resource_manager.hpp"


namespace t3 {
inline namespace gfx {
    

class Texture final
    : public Resource
{
    friend class TextureFactory;

public:
    ~Texture(){}
    
private:
    Texture(
        std::string name,
        const uint32_t width,
        const uint32_t height,
        const RenderSystem::ColorFormat color_format,
        const RenderSystem::texture_handle_t tex_handle
    );
    
    
public:
    
    //  横幅取得
    uint32_t getWidth() const {
        return width_;
    }
    
    //  縦幅取得
    uint32_t getHeight() const {
        return height_;
    }
    
    //  カラーフォーマット取得
    RenderSystem::ColorFormat getColorFormat() const {
        return color_format_;
    }
    
    //  テクスチャ生成
    static std::shared_ptr<Texture> create(
        const FilePath& filepath
    );
    
    void setupTexture();
    
private:
    
    //  サイズ
    uint32_t width_;
    uint32_t height_;

    //  カラーフォーマット
    RenderSystem::ColorFormat color_format_;
    RenderSystem::texture_handle_t texture_handle_;
};
    
using TextureManager = ResourceManager<Texture>;

    

}   // inline namespace gfx
}   // namespace t3

#endif // TRI_TEXTURE_HPP_INCLUDED
