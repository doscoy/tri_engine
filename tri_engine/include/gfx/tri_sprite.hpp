
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED



#include "../math/tri_math_types.hpp"
#include "../util/tri_uncopyable.hpp"
#include "tri_gfx_types.hpp"
#include <memory>
#include <cstdint>



namespace t3 {
inline namespace gfx {


class Texture;
class SpriteLayer;
class Sprite final
    : private Uncopyable 
{
    enum Priority {
        PRIORITY_LOWEST  = 10,
        PRIORITY_LOW     = 30,
        PRIORITY_NORMAL  = 50,
        PRIORITY_HIGH    = 80,
        PRIORITY_HIGHEST = 100
    };


    friend class SpriteLayer;

public:
    ~Sprite();
    
private:
    //  スプライトの直接生成禁止
    Sprite();
    
public:
    
    // *********************************************
    //  テクスチャを設定
    void setTexture( std::shared_ptr<Texture> tex );
    
    
    // *********************************************
    //  テクスチャ取得
    const std::shared_ptr<Texture>& getTexture() const {
        return texture_;
    }
    

    // *********************************************
    //  座標を取得
    Vec2& getPosition() {
        return position_;
    }
    
    
    // *********************************************
    //  座標を取得
    const Vec2& getPosition() const {
        return position_;
    }
    
    
    // *********************************************
    //  座標を設定
    void setPosition(
        const Vec2& pos
    ){
        position_ = pos;
    }
    
    
    // *********************************************
    //  座標を設定
    void setPosition(
        const float x,
        const float y
    ){
        position_.x_ = x;
        position_.y_ = y;
    }
    
    
    // *********************************************
    //  z軸回転を取得
    float getRotation() const {
        return rotation_;
    }
    

    // *********************************************
    //  z軸回転を設定
    void setRotation(
        const float rot
    ){
        rotation_ = rot;
    }


    // *********************************************
    //  回転中心を取得
    const Vec2& getPivot() const {
        return pivot_;
    }

    
    // *********************************************
    //  回転中心を設定
    void setPivot(
        const Vec2& pivot
    ){
        pivot_ = pivot;
    }

    
    // *********************************************
    //  回転中心を設定
    void setPivot(
        const float x,
        const float y
    ){
        pivot_.x_ = x;
        pivot_.y_ = y;
    }

    
    // *********************************************
    //  テクスチャ座標を取得
    const texture_coord_t& getTextureCoord() const {
        return texture_coord_;
    }


    // *********************************************
    //  テクスチャ座標を設定
    void setTextureCoord(
        const texture_coord_t& tex_coord
    ){
        texture_coord_ = tex_coord;
    }

    
    // *********************************************
    //  テクスチャ座標を設定
    void setTextureCoord(
        const float u0,
        const float v0,
        const float u1,
        const float v1
    ){
        texture_coord_.u0 = u0;
        texture_coord_.v0 = v0;
        texture_coord_.u1 = u1;
        texture_coord_.v1 = v1;
    }

    
    // *********************************************
    //  サイズを取得
    Vec2& getSize() {
        return size_;
    }
    
    
    // *********************************************
    //  サイズを取得
    const Vec2& getSize() const {
        return size_;
    }
    
    
    // *********************************************
    //  サイズを設定
    void setSize(
        const Vec2& size
    ){
        size_ = size;
    }
    
    // *********************************************
    //  スケールを取得
    Vec2& getScale() {
        return scale_;
    }


    // *********************************************
    //  スケールを取得
    const Vec2& getScale() const {
        return scale_;
    }
    
    
    // *********************************************
    //  スケールを設定
    void setScale(
        const Vec2& scale
    ){
        scale_ = scale;
    }
    
    
    // *********************************************
    //  描画プライオリティ取得
    uint8_t getPriority() const {
        return priority_;
    }
    
    
    // *********************************************
    //  描画プライオリティ設定
    void setPriority(
        const uint8_t priority
    ){
        priority_ = priority;
    }
    

    // *********************************************
    //  有効フラグ設定
    void setEnable(
        const bool enable
    ){
        enable_ = enable;
    }
    
    
    // *********************************************
    //  有効判定
    bool isEnable() const {
        return enable_;
    }

    void attachToLayer( SpriteLayer* const layer );
    void detachToLayer();
    void destroy();
    
    bool isValid() const;
    
private:
    std::shared_ptr<Texture> texture_;
    Vec2 position_;
    Vec2 size_;
    Vec2 pivot_;
    float rotation_;
    texture_coord_t texture_coord_;
    Vec2 scale_;
    uint8_t priority_;
    bool enable_;
    SpriteLayer* owner_;
};


}   // inline namespace gfx
}   // namespace t3


#endif // TRI_SPRITE_HPP_INCLUDED

