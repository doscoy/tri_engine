
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED



#include "math/tri_math_types.hpp"
#include "geometry/tri_transform.hpp"
#include "util/tri_uncopyable.hpp"
#include "tri_gfx_types.hpp"
#include "tri_render_system.hpp"
#include "dbg/tri_assert.hpp"
#include <memory>
#include <cstdint>



namespace t3 {
inline namespace gfx {


class Texture;
class SpriteLayer;

class Sprite final
    : private Uncopyable 
{
    friend class SpriteLayer;

public:
    enum Priority {
        PRIORITY_LOWEST     = 10,
        PRIORITY_LOW_1      = 130,
        PRIORITY_LOW_2      = 135,
        PRIORITY_LOW_3      = 140,
        PRIORITY_NORMAL     = 150,
        PRIORITY_HIGH_1     = 170,
        PRIORITY_HIGH_2     = 175,
        PRIORITY_HIGH_3     = 180,
        PRIORITY_UI_DEFAULT = 200,
        PRIORITY_HIGHEST    = 220
    };


public:
    ~Sprite();
    
private:
    //  スプライトの直接生成禁止
    Sprite();
    
public:
    
    //  テクスチャを設定
    void texture( std::shared_ptr<Texture> tex );
    
    
    //  テクスチャ取得
    const std::shared_ptr<Texture>& texture() const {
        return texture_;
    }
    
    void transform(
        const Transform2D& transform
    ) {
        position(transform.getGlobalPosition());
        rotation(transform.getGlobalRotation());
        scale(transform.scale());
    }


    //  座標を取得
    Vec2& position() {
        return position_;
    }
    
    
    //  座標を取得
    const Vec2& position() const {
        return position_;
    }
    
    
    //  座標を設定
    void position(
        const Vec2& pos
    ){
        position_ = pos;
    }
    
    
    //  座標を設定
    void position(
        const float x,
        const float y
    ){
        position_.x_ = x;
        position_.y_ = y;
    }
    
    //  向きを設定
    void direction(
        const Vec2& dir
    ) {
        float angle = std::atan2(dir.y_, dir.x_);
        rotation(t3::toDegree(angle));
    }


    
    //  回転を取得
    float rotation() const {
        return rotation_;
    }
    

    //  回転を設定
    void rotation(
        const float rot
    ){
        rotation_ = rot;
    }

    //  回転中心を取得
    const Vec2& pivot() const {
        return pivot_;
    }

    
    //  回転中心を設定
    void pivot(
        const Vec2& pivot
    ){
        pivot_ = pivot;
    }

    
    //  回転中心を設定
    void pivot(
        const float x,
        const float y
    ){
        pivot_.x_ = x;
        pivot_.y_ = y;
    }
    
    void adjustPivotByCenter();

    
    //  テクスチャ座標を取得
    const texture_coord_t& textureCoord() const {
        return texture_coord_;
    }

    //  テクスチャ座標を設定
    void textureCoord(
        const texture_coord_t& tex_coord
    ){
        texture_coord_ = tex_coord;
    }

    
    //  テクスチャ座標を設定
    void textureCoord(
        const float u0,
        const float v0,
        const float u1,
        const float v1
    ){
        texture_coord_.u0_ = u0;
        texture_coord_.v0_ = v0;
        texture_coord_.u1_ = u1;
        texture_coord_.v1_ = v1;
    }

    void textureCoord(
        const Vec2& left_top,
        const Vec2& size
    );
    
    void setupTextureCoordAndSize(
        const Vec2& left_top,
        const Vec2& size
    );

    
    //  サイズを取得
    Vec2& size() {
        return size_;
    }
    
    //  サイズを取得
    const Vec2& size() const {
        return size_;
    }
    
    
    //  サイズを設定
    void size(
        const Vec2& size
    ){
        size_ = size;
    }
    
    //  サイズを設定
    void size(
        const float w,
        const float h
    ) {
        size_.x_ = w;
        size_.y_ = h;
    }
    
    //  サイズを設定
    void size(
        const float s
    ) {
        size_.x_ = s;
        size_.y_ = s;
    }
    
    //  スケール済サイズを取得
    Vec2 scaledSize() const {
        Vec2 scaled = size() * scale();
        return scaled;
    }
    
    //  スケールを取得
    Vec2& scale() {
        return scale_;
    }


    //  スケールを取得
    const Vec2& scale() const {
        return scale_;
    }
    
    
    //  スケールを設定
    void scale(
        const Vec2& scale
    ){
        scale_ = scale;
    }
    
    void scale(
        const float scale
    ) {
        scale_.x_ = scale_.y_ = scale;
    }
    
    void scale(
        const float x,
        const float y
    ) {
        scale_.x_ = x;
        scale_.y_ = y;
    }
    
    
    //  描画プライオリティ取得
    uint8_t priority() const {
        return priority_;
    }
    
    
    //  描画プライオリティ設定
    void priority(
        const uint8_t priority
    ){
        priority_ = priority;
    }
    

    //  有効フラグ設定
    void enable(
        const bool enable
    ){
        enable_ = enable;
    }
    
    
    //  有効判定
    bool enable() const {
        return enable_;
    }
    
    int sortScore() const;
    


    bool isValid() const;

    void ownerLayer(SpriteLayer* layer) {
        owner_ = layer;
    }

    SpriteLayer* ownerLayer() const {
        return owner_;
    }
    
    bool isTransratedSprite() const {
        
        if (!isEqualFloat(position_.x_, 0.0f)) {
            return true;
        }
        if (!isEqualFloat(position_.y_, 0.0f)) {
            return true;
        }
        
        return false;
    }

    bool isRotatedSprite() const {
        
        if (isEqualFloat(rotation_, 0.0f)) {
            return false;
        }
        return true;
    }

    bool isScaledSprite() const {
       // return true;
        
        if (!isEqualFloat(scale_.x_, 1.0f)) {
            return true;
        }
        if (!isEqualFloat(scale_.y_, 1.0f)) {
            return true;
        }

        return false;
    }


    int opacity() const {
        return opacity_;
    }
    
    void opacity(
        const int opa
    ) {
        T3_ASSERT_RANGE(opa, 0, 255);
        opacity_ = opa;
    }


private:
    std::shared_ptr<Texture> texture_;
    Vec2 position_;
    Vec2 size_;
    Vec2 pivot_;
    Vec2 scale_;
    float rotation_;
    uint8_t opacity_;
    
    uint8_t priority_;
    texture_coord_t texture_coord_;
    
    bool enable_;
    SpriteLayer* owner_;
    
};

//  ポインタ型定義
using SpritePtr = std::shared_ptr<Sprite>;


}   // inline namespace gfx
}   // namespace t3


#endif // TRI_SPRITE_HPP_INCLUDED

