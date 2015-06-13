/**
    @file tri_texture_factory.hpp
    テクスチャファクトリ.
*/

#ifndef TRI_TEXTURE_FACTORY_HPP_INCLUDED
#define TRI_TEXTURE_FACTORY_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "base/tri_std.hpp"
#include "kernel/io/tri_filepath.hpp"
#include "tri_texture.hpp"


TRI_CORE_NS_BEGIN


///
/// テクスチャファクトリ
class TextureFactory {
public:
    ///
    ///
    static TexturePtr createFromFile(
        const FilePath& filename
    );

    ///
    ///
    static TexturePtr createFromFile(
        const File& file
    );
    
    ///
    /// テクスチャ生成.
    /// パラメータから生成
    static TexturePtr createFromData(
        String name,            ///< テクスチャ名
        const uint32_t width,   ///< 幅
        const uint32_t height,  ///< 高さ
        const cross::RenderSystem::ColorFormat color_format, ///< カラーフォーマット
        const cross::RenderSystem::TypeFormat type_format,
        const void* data        ///< データ
    );
    
    ///
    /// テクスチャを生成.
    /// ファイルパスから生成
    static TexturePtr createFromPngFile(
        const FilePath& filepath
    );

    ///
    /// テクスチャを生成.
    /// ファイルから生成
    static TexturePtr createFromPngFile(
        const File& file
    );
};



TRI_CORE_NS_END



#endif // TRI_TEXTURE_FACTORY_HPP_INCLUDED

