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

class Texture;
using TexturePtr = SharedPtr<Texture>;
class Texture final
    : public Resource
{
    friend class TextureFactory;

public:
    ~Texture();
    
private:
    Texture(
        String name,
        const uint32_t width,
        const uint32_t height,
        const RenderSystem::ColorFormat color_format
    );
    
    
public:
    
    //  横幅取得
    uint32_t width() const {
        return width_;
    }
    
    //  縦幅取得
    uint32_t height() const {
        return height_;
    }
    
    //  カラーフォーマット取得
    RenderSystem::ColorFormat getColorFormat() const {
        return color_format_;
    }
    
    void setWrapMode(
        RenderSystem::TextureWrapType type
    ) {
        bind();
        RenderSystem::setTextureWrap(type);
    }
    
    
    
    //  テクスチャ生成
    static TexturePtr create(
        const FilePath& filepath
    );
    
    static TexturePtr create(
        String name,
        const int width,
        const int height,
        const RenderSystem::ColorFormat
    );
    
    static TexturePtr create(
        const File& file
    );
    
    
    void bind();
    
    RenderSystem::TextureID id() {
        return texture_handle_;
    }
    
public:
    bool operator == (const Texture& rhs) {
        return (resourceID() == rhs.resourceID());
    }
    
    bool operator != (const Texture& rhs) {
        return !(operator==(rhs));
    }
    
private:
    
    //  サイズ
    uint32_t width_;
    uint32_t height_;

    //  カラーフォーマット
    RenderSystem::ColorFormat color_format_;
    RenderSystem::TextureID texture_handle_;
};
    

using TextureManager = ResourceManager<Texture>;

    

}   // inline namespace gfx
}   // namespace t3

#endif // TRI_TEXTURE_HPP_INCLUDED
