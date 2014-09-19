
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED



#include "math/tri_math_types.hpp"
#include "geometry/tri_transform.hpp"
#include "util/tri_uncopyable.hpp"
#include "tri_gfx_types.hpp"
#include "tri_render_system.hpp"
#include "dbg/tri_assert.hpp"
#include "tri_texture.hpp"
#include "base/tri_std.hpp"



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
    void texture( TexturePtr tex );
    
    
    //  テクスチャ取得
    const TexturePtr& texture() const {
        return texture_;
    }
    
    void setParentTransform(
        const Transform2DPtr transform
    ) {
        transform_->setParentTransform(transform);
    }

    Transform2DPtr transform() {
        return transform_;
    }
    
    const Transform2DPtr transform() const {
        return transform_;
    }
    
    void transform(
        Transform2DPtr t
    ) {
        transform_ = t;
    }


    
    //  向きを設定
    void direction(
        const Vec2& dir
    ) {
        float angle = std::atan2(dir.y_, dir.x_);
        transform_->rotation(t3::toDegree(angle));
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
        Vec2 scaled = size() * transform()->scale();
        return scaled;
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
    void enable() {
        enable_ = true;
    }
    
    void disable() {
        enable_ = false;
    }
    
    
    //  有効判定
    bool enabled() const {
        return enable_;
    }
    
    int sortScore() const;
    

    
    bool isTransratedSprite() const {
        Vec2 pos = transform()->globalPosition();
        if (!isEqualFloat(pos.x_, 0.0f)) {
            return true;
        }
        if (!isEqualFloat(pos.y_, 0.0f)) {
            return true;
        }
        
        return false;
    }

    bool isRotatedSprite() const {
        float rot = transform()->globalRotation();
        if (isEqualFloat(rot, 0.0f)) {
            return false;
        }
        return true;
    }

    bool isScaledSprite() const {
        const Vec2& scale = transform()->scale();
        
        if (!isEqualFloat(scale.x_, 1.0f)) {
            return true;
        }
        if (!isEqualFloat(scale.y_, 1.0f)) {
            return true;
        }

        return false;
    }


    const Color& color() const {
        return color_;
    }
    
    void color(const Color& color) {
        color_ = color;
    }

    int opacity() const {
        return color_.alpha_;
    }
    
    void opacity(
        const int opa
    ) {
        T3_ASSERT_RANGE(opa, 0, 255);
        color_.alpha_ = opa;
    }


private:
    TexturePtr texture_;
    Transform2DPtr transform_;
    Vec2 size_;
    Vec2 pivot_;

    Color color_;
    
    uint8_t priority_;
    texture_coord_t texture_coord_;
    
    bool enable_;
    
};

//  ポインタ型定義
using SpritePtr = SharedPtr<Sprite>;
using WeakSprite = std::weak_ptr<Sprite>;



}   // inline namespace gfx
}   // namespace t3


#endif // TRI_SPRITE_HPP_INCLUDED

