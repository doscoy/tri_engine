#ifndef TRI_TEXTURE_HPP_INCLUDED
#define TRI_TEXTURE_HPP_INCLUDED

#include "../util/tri_unique_id.hpp"
#include "../math/tri_vec2.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../kernel/tri_resource.hpp"
#include "../gfx/tri_color.hpp"

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
        const char* const name,
        const int width,
        const int height,
        const ColorFormat color_format,
        const int8_t* data
    );    
    
    
public:
    // *********************************************
    // サイズ取得
    const Point2& getSize() const {
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
    const int8_t* getData() const override {
        return data_;
    }

    
    // *********************************************
    //  テクスチャ生成
    static std::shared_ptr<Texture> create(
        const char* const filepath
    );
    
    
    
private:
    
    //  サイズ
    Point2 size_;

    //  カラーフォーマット
    ColorFormat color_format_;
    
    const int8_t* data_;
};
    
    
    
    

}   // inline namespace gfx
}   // namespace t3

#endif // TRI_TEXTURE_HPP_INCLUDED
