
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED



#include "math/tri_math_types.hpp"
#include "geometry/tri_transform.hpp"
#include "util/tri_uncopyable.hpp"
#include "tri_gfx_types.hpp"
#include "tri_render_system.hpp"
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
    
    //  テクスチャを設定
    void setTexture( std::shared_ptr<Texture> tex );
    
    
    //  テクスチャ取得
    const std::shared_ptr<Texture>& getTexture() const {
        return texture_;
    }
    
    void setTransform(
        const Transform2D& transform
    ) {
        setPosition(transform.getPosition());
        setRotation(transform.getRotation());
        setScale(transform.getScale());
    }


    //  座標を取得
    Vec2& getPosition() {
        return position_;
    }
    
    
    //  座標を取得
    const Vec2& getPosition() const {
        return position_;
    }
    
    
    //  座標を設定
    void setPosition(
        const Vec2& pos
    ){
        position_ = pos;
    }
    
    
    //  座標を設定
    void setPosition(
        const float x,
        const float y
    ){
        position_.x_ = x;
        position_.y_ = y;
    }
    
    //  向きを設定
    void setDirection(
        const Vec2& dir
    ) {
        float angle = std::atan2(dir.x_, dir.y_);
        setRotation(t3::toDegree(angle));
    }


    
    //  回転を取得
    float getRotation() const {
        return rotation_;
    }
    

    //  回転を設定
    void setRotation(
        const float rot
    ){
        rotation_ = rot;
    }

    //  回転中心を取得
    const Vec2& getPivot() const {
        return pivot_;
    }

    
    //  回転中心を設定
    void setPivot(
        const Vec2& pivot
    ){
        pivot_ = pivot;
    }

    
    //  回転中心を設定
    void setPivot(
        const float x,
        const float y
    ){
        pivot_.x_ = x;
        pivot_.y_ = y;
    }
    
    void setPivotByCenter();

    
    //  テクスチャ座標を取得
    const texture_coord_t& getTextureCoord() const {
        return texture_coord_;
    }

    //  テクスチャ座標を設定
    void setTextureCoord(
        const texture_coord_t& tex_coord
    ){
        texture_coord_ = tex_coord;
    }

    
    //  テクスチャ座標を設定
    void setTextureCoord(
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
    
    void setTextureCoordAndSizeByST(
        const Vec2& left_top,
        const Vec2& size
    );

    
    //  サイズを取得
    Vec2& getSize() {
        return size_;
    }
    
    //  サイズを取得
    const Vec2& getSize() const {
        return size_;
    }
    
    
    //  サイズを設定
    void setSize(
        const Vec2& size
    ){
        size_ = size;
    }
    
    //  スケールを取得
    Vec2& getScale() {
        return scale_;
    }


    //  スケールを取得
    const Vec2& getScale() const {
        return scale_;
    }
    
    
    //  スケールを設定
    void setScale(
        const Vec2& scale
    ){
        scale_ = scale;
    }
    
    void setScale(
        const float scale
    ) {
        scale_.x_ = scale_.y_ = scale;
    }
    
    void setScale(
        const float x,
        const float y
    ) {
        scale_.x_ = x;
        scale_.y_ = y;
    }
    
    
    //  描画プライオリティ取得
    uint8_t getPriority() const {
        return priority_;
    }
    
    
    //  描画プライオリティ設定
    void setPriority(
        const uint8_t priority
    ){
        priority_ = priority;
    }
    

    //  有効フラグ設定
    void setEnable(
        const bool enable
    ){
        enable_ = enable;
    }
    
    
    //  有効判定
    bool isEnable() const {
        return enable_;
    }
    
    int getSortScore() const;
    


    bool isValid() const;

    void setAttachedLayer(SpriteLayer* layer) {
        owner_ = layer;
    }

    SpriteLayer* getAttachedLayer() const {
        return owner_;
    }


private:
    std::shared_ptr<Texture> texture_;
    Vec2 position_;
    Vec2 size_;
    Vec2 pivot_;
    Vec2 scale_;
    float rotation_;
    
    uint8_t priority_;
    texture_coord_t texture_coord_;
    
    bool enable_;
    SpriteLayer* owner_;
    
};


}   // inline namespace gfx
}   // namespace t3


#endif // TRI_SPRITE_HPP_INCLUDED

