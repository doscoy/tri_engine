
#ifndef TRI_SPRITE_HPP_INCLUDED
#define TRI_SPRITE_HPP_INCLUDED



#include "../math/tri_math_types.hpp"
#include "../util/tri_uncopyable.hpp"
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
        calc_matrix_request_ = true;
    }
    
    
    // *********************************************
    //  座標を設定
    void setPosition(
        const float x,
        const float y
    ){
        position_.x_ = x;
        position_.y_ = y;
        calc_matrix_request_ = true;
    }
    
    void addPosition(
        const Vec2& add
    ) {
        position_ += add;
        calc_matrix_request_;
    }
    
    // *********************************************
    //  回転を取得
    const Vec3* getRotation() const {
        return &rotation_;
    }
    

    // *********************************************
    //  回転を設定
    void setRotation(
        const Vec3& rot
    ){
        calc_matrix_request_ = true;
        rotation_ = rot;
    }
    
    void addRotationX(float r) {
        calc_matrix_request_ = true;
        rotation_.x_ += r;
    }

    void addRotationY(float r) {
        calc_matrix_request_ = true;
        rotation_.y_ += r;
    }
    
    void addRotationZ(float r) {
        calc_matrix_request_ = true;
        rotation_.z_ += r;
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
        calc_matrix_request_ = true;
        pivot_ = pivot;
    }

    
    // *********************************************
    //  回転中心を設定
    void setPivot(
        const float x,
        const float y
    ){
        calc_matrix_request_ = true;
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
        setupVertexBuffer();
    }

    
    // *********************************************
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
        setupVertexBuffer();
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
        setupVertexBuffer();
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
        calc_matrix_request_ = true;
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
    
    
    const Mtx4* getMatrix();
    
    
    int getSortScore() const;
    
    RenderSystem::buffer_id_t getVertexBuffer() const {
        return vertex_buffer_;
    }
    
    RenderSystem::buffer_id_t getIndexBuffer() const {
        return index_buffer_;
    }
    

    bool isValid() const;

    void setAttachedLayer(SpriteLayer* layer) {
        owner_ = layer;
    }

    SpriteLayer* getAttachedLayer() const {
        return owner_;
    }

private:
    void calcMatrix();
    void setupVertexBuffer();
private:
    std::shared_ptr<Texture> texture_;
    Vec2 position_;
    Vec2 size_;
    Vec2 pivot_;
    Vec3 rotation_;
    texture_coord_t texture_coord_;
    Vec2 scale_;
    uint8_t priority_;
    bool enable_;
    SpriteLayer* owner_;
    bool calc_matrix_request_;
    Mtx4 matrix_;
    
    
    RenderSystem::buffer_id_t vertex_buffer_;
    RenderSystem::buffer_id_t index_buffer_;
    
};


}   // inline namespace gfx
}   // namespace t3


#endif // TRI_SPRITE_HPP_INCLUDED

