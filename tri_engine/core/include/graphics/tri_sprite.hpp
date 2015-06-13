/**
    @file tri_sprite.hpp
    スプライト.
*/
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED


//  include
#include "core_config.hpp"
#include "math/tri_math_types.hpp"
#include "geometry/tri_transform.hpp"
#include "geometry/tri_rectangle.hpp"
#include "utility/tri_uncopyable.hpp"
#include "tri_gfx_types.hpp"
#include "debug/tri_assert.hpp"
#include "tri_texture.hpp"
#include "base/tri_std.hpp"



TRI_CORE_NS_BEGIN


//  前方宣言
class Texture;
class SpriteLayer;

///
/// スプライト
class Sprite final
    : private Uncopyable 
{
    friend class SpriteLayer;

public:
    ///
    /// プライオリティ
    enum Priority {
        PRIORITY_LOWEST     = 10,
        PRIORITY_LOW_1      = 50,
        PRIORITY_LOW_2      = 70,
        PRIORITY_LOW_3      = 90,
        PRIORITY_NORMAL     = 120,
        PRIORITY_HIGH_1     = 150,
        PRIORITY_HIGH_2     = 170,
        PRIORITY_HIGH_3     = 190,
        PRIORITY_UI_DEFAULT = 210,
        PRIORITY_HIGHEST    = 250
    };


public:
    ///
    /// デストラクタ
    ~Sprite();
    
private:
    ///
    ///  スプライトの直接生成禁止
    Sprite();
    
public:
    ///
    ///  テクスチャを設定
    void texture( TexturePtr tex );
    
    ///
    ///  テクスチャ取得
    TexturePtr& texture() {
        return texture_;
    }
    
    ///
    /// テクスチャ取得
    const TexturePtr& texture() const {
        return texture_;
    }
    
    ///
    /// 親の姿勢制御情報を設定
    void parent(
        const Transform2DPtr transform
    ) {
        transform_->parent(transform);
    }

    ///
    /// 姿勢制御情報取得
    Transform2DPtr transform() {
        return transform_;
    }
    
    ///
    /// 姿勢制御情報取得
    const Transform2DPtr transform() const {
        return transform_;
    }
    
    ///
    /// 姿勢制御情報設定
    void transform(
        Transform2DPtr t
    ) {
        transform_ = t;
    }

    ///
    ///  矩形
    Rectangle& rectangle() {
        return rectangle_;
    }
    
    ///
    /// 矩形を取得
    const Rectangle& rectangle() const {
        return rectangle_;
    }
    
    ///
    ///  向きを設定
    void direction(
        const Vec2& dir
    ) {
        float angle = std::atan2(dir.y_, dir.x_);
        transform_->rotation(
            t3::Vec3(
                0.0f,
                0.0f,
                t3::toDegree(angle)
            )
        );
    }

    ///
    ///  回転中心を取得
    const Vec2& pivot() const {
        return pivot_;
    }

    ///
    ///  回転中心を設定
    void pivot(
        const Vec2& pivot
    ){
        pivot_ = pivot;
    }

    ///
    ///  回転中心を設定
    void pivot(
        const float x,
        const float y
    ){
        pivot_.x_ = x;
        pivot_.y_ = y;
    }
    
    ///
    /// Pivotを中心に設定
    void adjustPivotByCenter();

    ///
    ///  テクスチャ座標を取得
    const texture_coord_t& textureCoord() const {
        return texture_coord_;
    }

    ///
    ///  テクスチャ座標を設定
    void textureCoord(
        const texture_coord_t& tex_coord
    ){
        texture_coord_ = tex_coord;
    }

    ///
    ///  テクスチャ座標を設定
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

    ///
    /// テクスチャUVを設定
    void textureCoord(
        const Vec2& left_top,
        const Vec2& size
    );
    
    ///
    /// テクスチャUVを設定
    void setupTextureCoordAndSize(
        const Vec2& left_top,
        const Vec2& size
    );

    ///
    ///  サイズを取得
    Vec2& size() {
        return size_;
    }
    
    ///
    ///  サイズを取得
    const Vec2& size() const {
        return size_;
    }
    
    ///
    ///  サイズを設定
    void size(
        const Vec2& size
    ){
        size_ = size;
    }
    
    ///
    ///  サイズを設定
    void size(
        const float w,
        const float h
    ) {
        size_.x_ = w;
        size_.y_ = h;
    }
    
    ///
    ///  サイズを設定
    void size(
        const float s
    ) {
        size_.x_ = s;
        size_.y_ = s;
    }
    
    ///
    ///  スケール済サイズを取得
    Vec2 scaledSize() const {
        Vec2 scaled = size() * transform()->scale();
        return scaled;
    }

    ///
    ///  描画プライオリティ取得
    uint8_t priority() const {
        return priority_;
    }
    
    ///
    ///  描画プライオリティ設定
    void priority(
        const uint8_t priority
    ){
        priority_ = priority;
        calcSortScore();
    }
    
    ///
    ///  有効化
    void enable() {
        enable_ = true;
    }
    
    ///
    /// 無効化
    void disable() {
        enable_ = false;
    }
    
    ///
    ///  有効判定
    bool enabled() const {
        return enable_;
    }
    
    ///
    /// ソート用スコアを取得
    int sortScore() const;
    

    ///
    /// 色を取得
    const Color& color() const {
        return color_;
    }
    
    ///
    /// 色を設定
    void color(
        const Color& color  ///< カラー値
    ) {
        auto a = color_.alpha();
        color_ = color;
        color_.alpha(a);
    }

    ///
    /// 不透明度を取得
    int opacity() const {
        return color_.alpha();
    }
    
    ///
    /// 不透明度を設定
    void opacity(
        const int opa   ///< 不透明度
    ) {
        T3_ASSERT_RANGE((float)opa, 0.0f, 255.0f);
        color_.alpha(opa);
    }

    ///
    /// ブレンドモードを取得
    cross::RenderSystem::BlendMode blendMode() const {
        return blend_mode_;
    }
    
    ///
    /// ブレンドモードを設定
    void blendMode(
        const cross::RenderSystem::BlendMode b  ///< ブレンドモード
    ) {
        blend_mode_ = b;
        calcSortScore();
    }
    
    ///
    /// ソート用のスコアを計算
    void calcSortScore();
    

private:
    ///
    /// テクスチャ
    TexturePtr texture_;
    
    ///
    /// 2D姿勢制御
    Transform2DPtr transform_;
    
    ///
    /// サイズ
    Vec2 size_;
    
    ///
    /// 回転中心点
    Vec2 pivot_;

    ///
    /// 色
    Color color_;
    
    ///
    /// 矩形
    Rectangle rectangle_;
    
    ///
    /// ブレンドモード
    cross::RenderSystem::BlendMode blend_mode_;
    
    
    ///
    /// プライオリティ
    uint8_t priority_;
    
    ///
    /// テクスチャUV
    texture_coord_t texture_coord_;
    
    ///
    /// ソート用スコア
    int sort_score_;
    
    ///
    /// 有効判定
    bool enable_;
    
};

//  ポインタ型定義
using SpritePtr = SharedPtr<Sprite>;
using WeakSprite = std::weak_ptr<Sprite>;


TRI_CORE_NS_END


#endif // TRI_SPRITE_HPP_INCLUDED

