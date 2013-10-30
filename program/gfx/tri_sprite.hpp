
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED


#include "../tri_develop_base.hpp"
#include "../math/tri_math_types.hpp"
#include "../util/tri_uncopyable.hpp"
#include "tri_gfx_types.hpp"





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
    const Texture* getTexture() const {
        return texture_.get();
    }
    

    // *********************************************
    //  座標を取得
    vec2_t& getPosition() {
        return position_;
    }
    
    
    // *********************************************
    //  座標を取得
    const vec2_t& getPosition() const {
        return position_;
    }
    
    
    // *********************************************
    //  座標を設定
    void setPosition(
        const vec2_t& pos
    ){
        position_ = pos;
    }
    
    
    // *********************************************
    //  座標を設定
    void setPosition(
        const float x,
        const float y
    ){
        position_.x = x;
        position_.y = y;
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
    const vec2_t& getPivot() const {
        return pivot_;
    }

    
    // *********************************************
    //  回転中心を設定
    void setPivot(
        const vec2_t& pivot
    ){
        pivot_ = pivot;
    }

    
    // *********************************************
    //  回転中心を設定
    void setPivot(
        const float x,
        const float y
    ){
        pivot_.x = x;
        pivot_.y = y;
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
    vec2_t& getSize() {
        return size_;
    }
    
    
    // *********************************************
    //  サイズを取得
    const vec2_t& getSize() const {
        return size_;
    }
    
    
    // *********************************************
    //  サイズを設定
    void setSize(
        const vec2_t& size
    ){
        size_ = size;
    }
    
    // *********************************************
    //  スケールを取得
    vec2_t& getScale() {
        return scale_;
    }


    // *********************************************
    //  スケールを取得
    const vec2_t& getScale() const {
        return scale_;
    }
    
    
    // *********************************************
    //  スケールを設定
    void setScale(
        const vec2_t& scale
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

    void attachLayer( SpriteLayer* const layer );
    void detachLayer();
    void destroy();
    
    bool isValid() const;
    
private:
    std::shared_ptr<Texture> texture_;
    vec2_t position_;
    vec2_t size_;
    vec2_t pivot_;
    float rotation_;
    texture_coord_t texture_coord_;
    vec2_t scale_;
    uint8_t priority_;
    bool enable_;
    SpriteLayer* owner_;
};


}   // inline namespace gfx
}   // namespace t3


#endif // TRI_SPRITE_HPP_INCLUDED

