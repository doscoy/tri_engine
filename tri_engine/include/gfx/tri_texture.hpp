/**
    @file tri_texture.hpp
    テクスチャ.
*/
#ifndef TRI_TEXTURE_HPP_INCLUDED
#define TRI_TEXTURE_HPP_INCLUDED

//  include
#include "../util/tri_unique_id.hpp"
#include "../math/tri_vec2.hpp"
#include "../base/tri_resource.hpp"
#include "../gfx/tri_color.hpp"
#include "base/tri_resource_manager.hpp"


namespace t3 {

//  前方宣言
class Texture;
using TexturePtr = SharedPtr<Texture>;

///
/// テクスチャ
class Texture final
    : public Resource
{
    friend class TextureFactory;

public:
    ///
    /// デストラクタ
    ~Texture();
    
private:
    ///
    /// コンストラクタ
    Texture(
        String name,            ///< 名前
        const uint32_t width,   ///< 幅
        const uint32_t height,  ///< 高さ
        const cross::RenderSystem::ColorFormat color_format, ///< カラーフォーマット
        const cross::RenderSystem::TypeFormat type_format,   ///< 型フォーマット
        uint8_t* data     ///< ピクセルデータ
    );
    
    
public:
    
    ///
    ///  横幅取得
    uint32_t width() const {
        return width_;
    }
    
    ///
    ///  縦幅取得
    uint32_t height() const {
        return height_;
    }
    
    ///
    ///  カラーフォーマット取得
    cross::RenderSystem::ColorFormat getColorFormat() const {
        return color_format_;
    }
    
    ///
    /// ラップモード設定
    void setWrapMode(
        cross::RenderSystem::TextureWrapType type   ///< モード
    ) {
        bind();
        cross::RenderSystem::setTextureWrap(type);
    }
    
    
    ///
    ///  テクスチャ生成
    static TexturePtr create(
        const FilePath& filepath    ///< ファイルパス
    );
    
    ///
    /// テクスチャ生成
    static TexturePtr create(
        String name,        ///< 名前
        const uint32_t width,    ///< 幅
        const uint32_t height,   ///< 高さ
        const cross::RenderSystem::ColorFormat cf,   ///< カラーフォーマット
        const cross::RenderSystem::TypeFormat tf,    ///< 型フォーマット
        uint8_t* data
    );
    
    ///
    /// テクスチャ生成
    static TexturePtr create(
        const File& file    ///< ファイル
    );
    
    
    ///
    /// テクスチャをバインド
    void bind();
    
    ///
    /// テクスチャID取得
    cross::RenderSystem::TextureID id() {
        return texture_handle_;
    }
    
public:
    ///
    /// operator ==
    bool operator == (const Texture& rhs) {
        return (resourceID() == rhs.resourceID());
    }
    
    ///
    /// operator !=
    bool operator != (const Texture& rhs) {
        return !(operator==(rhs));
    }
    
private:
    ///
    /// テクスチャ幅
    uint32_t width_;

    ///
    /// テクスチャ高さ
    uint32_t height_;

    ///
    /// カラーフォーマット
    cross::RenderSystem::ColorFormat color_format_;
    
    ///
    /// 型フォーマット
    cross::RenderSystem::TypeFormat type_format_;


    ///
    /// テクスチャハンドル
    cross::RenderSystem::TextureID texture_handle_;
};
    

using TextureManager = ResourceManager<Texture>;

    
}   // namespace t3

#endif // TRI_TEXTURE_HPP_INCLUDED
