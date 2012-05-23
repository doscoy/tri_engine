
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED


#include "../tri_develop_base.hpp"
#include "../math/tri_vector.hpp"
#include "../util/tri_uncopyable.hpp"
#include "tri_gfx_types.hpp"





namespace t3 {

constexpr u_char SPRITE_RENDER_PRIORITY_LOW     = 8;
constexpr u_char SPRITE_RENDER_PRIORITY_DEFAULT = 16;
constexpr u_char SPRITE_RENDER_PRIORITY_HIGH    = 24;

class Texture;
class Sprite final
    : private Uncopyable 
{    
public:
    Sprite();
    ~Sprite();
    
public:
    
    // *********************************************
    //  テクスチャを設定
    void setTexture( const Texture& tex );
    
    
    // *********************************************
    //  テクスチャ取得
    const Texture& getTexture() const {
        return *texture_;
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
    u_char getPriority() const {
        return priority_;
    }
    
    
    // *********************************************
    //  描画プライオリティ設定
    void setPriority(
        const u_char priority
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

    
private:
    const Texture* texture_;
    vec2_t position_;
    vec2_t size_;
    vec2_t pivot_;
    float rotation_;
    texture_coord_t texture_coord_;
    vec2_t scale_;
    u_char priority_;
    bool enable_;

};


    
} // namespace t3


#endif // TRI_SPRITE_HPP_INCLUDED

