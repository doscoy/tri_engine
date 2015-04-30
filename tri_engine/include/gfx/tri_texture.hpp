#ifndef TRI_TEXTURE_HPP_INCLUDED
#define TRI_TEXTURE_HPP_INCLUDED

#include "../util/tri_unique_id.hpp"
#include "../math/tri_vec2.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../base/tri_resource.hpp"
#include "../gfx/tri_color.hpp"

#include "base/tri_resource_manager.hpp"


namespace t3 {

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
        const cross::RenderSystem::ColorFormat color_format
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
    cross::RenderSystem::ColorFormat getColorFormat() const {
        return color_format_;
    }
    
    void setWrapMode(
        cross::RenderSystem::TextureWrapType type
    ) {
        bind();
        cross::RenderSystem::setTextureWrap(type);
    }
    
    
    
    //  テクスチャ生成
    static TexturePtr create(
        const FilePath& filepath
    );
    
    static TexturePtr create(
        String name,
        const int width,
        const int height,
        const cross::RenderSystem::ColorFormat
    );
    
    static TexturePtr create(
        const File& file
    );
    
    
    void bind();
    
    cross::RenderSystem::TextureID id() {
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
    cross::RenderSystem::ColorFormat color_format_;
    cross::RenderSystem::TextureID texture_handle_;
};
    

using TextureManager = ResourceManager<Texture>;

    
}   // namespace t3

#endif // TRI_TEXTURE_HPP_INCLUDED
