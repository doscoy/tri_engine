#ifndef TRI_TEXTURE_HPP_INCLUDED
#define TRI_TEXTURE_HPP_INCLUDED

#include "../util/tri_unique_id.hpp"
#include "../math/tri_vec2.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../kernel/tri_resource.hpp"
#include "../gfx/tri_color.hpp"

namespace t3 {
    
class Texture final
    : public Resource
{
    friend class TextureFactory;
    
private:
    Texture(
        const char* const name,
        const int width,
        const int height,
        const ColorFormat color_format,
        const byte* data
    );    
    ~Texture(){}
    
    
public:
    // *********************************************
    // サイズ取得
    const ivec2_t& getSize() const {
        return size_;
    };
    
    // *********************************************
    //  横幅取得
    float getWidth() const {
        return size_.x;
    }
    
    // *********************************************
    //  縦幅取得
    float getHeight() const {
        return size_.y;
    }
    
    // *********************************************
    //  カラーフォーマット取得
    ColorFormat getColorFormat() const {
        return color_format_;
    }
    
    
    // *********************************************
    //  イメージデータ取得
    const byte* getData() const override {
        return data_;
    }

    
    // *********************************************
    //  テクスチャ生成
    static Texture* create(
        const char* const filepath
    );
    
    
    
private:
    
    //  サイズ
    ivec2_t size_;

    //  カラーフォーマット
    ColorFormat color_format_;
    
    const byte* data_;
};
    
    
    
    
    
    

}   // namespace t3

#endif // TRI_TEXTURE_HPP_INCLUDED
