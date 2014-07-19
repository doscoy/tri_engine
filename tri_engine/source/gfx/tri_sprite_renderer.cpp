
#include "tri_sprite_renderer.hpp"
#include "tri_sprite.hpp"
#include "tri_vertex_types.hpp"
#include "base/tri_director.hpp"
#include "tri_texture.hpp"
#include "math/tri_matrix.hpp"
#include "gfx/tri_render_system.hpp"
#include <algorithm>


#include "../shader/tri_sprite.vsh"
#include "../shader/tri_sprite.fsh"


namespace {

class PriorityCompare
{
public:
    bool operator()(const t3::SpritePtr lhs, const t3::SpritePtr rhs) const {
        return lhs->getSortScore() < rhs->getSortScore();
    }
};


  
}

namespace t3 {
inline namespace gfx {

SpriteRenderer::SpriteRenderer()
    : sprites_()
    , sprite_shader_()
{

    sprite_shader_.compileShaderFromString(
        sprite_vsh,
        RenderSystem::ShaderType::VERTEX_SHADER
    );
    sprite_shader_.compileShaderFromString(
        sprite_fsh,
        RenderSystem::ShaderType::FRAGMENT_SHADER
    );
    bool link_result = sprite_shader_.link();
    T3_ASSERT(link_result);
    
    //  スプライトコンテナのメモリを事前に確保
    sprites_.reserve(2000);
    
    
    RenderSystem::createBuffer(&index_buffer_);
    RenderSystem::createBuffer(&vertex_buffer_);

}
    

SpriteRenderer::~SpriteRenderer()
{

    RenderSystem::deleteBuffer(&index_buffer_);
    RenderSystem::deleteBuffer(&vertex_buffer_);

}



void SpriteRenderer::collectSprite(
    SpritePtr sprite
){
    sprites_.push_back(sprite);
}





void SpriteRenderer::render()
{
    if (sprites_.empty()) {
        //  描画すべきスプライトが無い場合は即終了
        return;
    }

    //  レンダリング設定
    beginRender();
    margeSprites();
    renderSprites();
    endRender();
    
}

void SpriteRenderer::beginRender()
{
    bool use_result = sprite_shader_.use();
    T3_ASSERT(use_result);
    //  スプライトのソート
//    std::sort(sprites_.begin(), sprites_.end(), PriorityCompare());

    sprite_shader_.setEnableAttributeArray("position", true);
    sprite_shader_.setEnableAttributeArray("uv", true );
    
    //頂点配列を有効化
    sprite_shader_.setUniform("sampler", 0);
    

    RenderSystem::setActiveTextureUnit(RenderSystem::TextureUnit::UNIT0);

    t3::RenderSystem::setBlendFunctionType(
        t3::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        t3::RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
    );

    t3::RenderSystem::setTextureMapping(true);
    t3::RenderSystem::setBlend(true);
    t3::RenderSystem::setCulling(false);


}


void SpriteRenderer::margeSprites() {

    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    
    vertices.reserve(sprites_.size() * 16);
    indices.reserve(sprites_.size() * 6);


    Vec2 screen_size = Director::getInstance().getScreenSize();
    Vec2 half = screen_size / 2;
    half.x_ = 1.0f / half.x_;
    half.y_ = 1.0f / half.y_;
    
    for (int i = 0; i < sprites_.size(); ++i) {
        auto spr = sprites_[i];
    
        const Vec2& pivot = spr->getPivot();
        const Vec2& size = spr->getSize();
        const texture_coord_t& uv = spr->getTextureCoord();

        //  初期配置
        Vec2 lt = Vec2(      0 - pivot.x_, size.y_ - pivot.y_);
        Vec2 lb = Vec2(      0 - pivot.x_, 0 - pivot.y_);
        Vec2 rt = Vec2(size.x_ - pivot.x_, size.y_ - pivot.y_);
        Vec2 rb = Vec2(size.x_ - pivot.x_, 0 - pivot.y_);
        
        //  スケーリング
        if (spr->isScaledSprite()) {
            const Vec2& scale = spr->getScale();
            lt *= scale;
            lb *= scale;
            rt *= scale;
            rb *= scale;
        }

        //  回転
        if (spr->isRotatedSprite()) {
            float angle = toRadian(spr->getRotation());

            float cos_angle = std::cos(angle);
            float sin_angle = std::sin(angle);
            {
                float ltx = lt.x_;
                float lty = lt.y_;
                lt.x_ = (ltx * cos_angle) - (lty * sin_angle);
                lt.y_ = (ltx * sin_angle) + (lty * cos_angle);
            }
        
            {
                float lbx = lb.x_;
                float lby = lb.y_;
                lb.x_ = (lbx * cos_angle) - (lby * sin_angle);
                lb.y_ = (lbx * sin_angle) + (lby * cos_angle);
            }
            {
                float rtx = rt.x_;
                float rty = rt.y_;
                rt.x_ = (rtx * cos_angle) - (rty * sin_angle);
                rt.y_ = (rtx * sin_angle) + (rty * cos_angle);
            }
        
            {
                float rbx = rb.x_;
                float rby = rb.y_;
                rb.x_ = (rbx * cos_angle) - (rby * sin_angle);
                rb.y_ = (rbx * sin_angle) + (rby * cos_angle);
            }
        }
        
        //  位置移動
        if (spr->isTransratedSprite()) {
            const Vec2& pos =spr->getPosition();

            lt += pos;
            lb += pos;
            rt += pos;
            rb += pos;
        }
        
        lt *= half;
        lb *= half;
        rt *= half;
        rb *= half;

        //  頂点バッファは普通に並べる
        vertices.push_back(lt.x_);
        vertices.push_back(lt.y_);
        vertices.push_back(uv.u0_);
        vertices.push_back(uv.v0_);
        
        vertices.push_back(lb.x_);
        vertices.push_back(lb.y_);
        vertices.push_back(uv.u0_);
        vertices.push_back(uv.v1_);

        vertices.push_back(rt.x_);
        vertices.push_back(rt.y_);
        vertices.push_back(uv.u1_);
        vertices.push_back(uv.v0_);

        vertices.push_back(rb.x_);
        vertices.push_back(rb.y_);
        vertices.push_back(uv.u1_);
        vertices.push_back(uv.v1_);

        int first_vertex_index = i * 4;

        //  インデックスバッファ
        if (i > 0) {
            //  ２スプライト目からは縮退ポリゴンを仕込む
            indices.push_back(first_vertex_index);
        }
        
        indices.push_back(first_vertex_index);
        indices.push_back(first_vertex_index + 1);
        indices.push_back(first_vertex_index + 2);
        indices.push_back(first_vertex_index + 3);
   
        
        
        if (i != sprites_.size() -1) {
            //  最後のスプライト以外は縮退ポリゴンを仕込む
            indices.push_back(first_vertex_index + 3);
        }
    }
    draw_count_ = static_cast<int>(indices.size());
    
    //  バッファ更新
    RenderSystem::bindBuffer(
        t3::RenderSystem::BufferType::TYPE_VERTEX,
        vertex_buffer_
    );
    RenderSystem::setupBufferData(
        t3::RenderSystem::BufferType::TYPE_VERTEX,
        static_cast<int>(vertices.size() * sizeof(float)),
        vertices.data(),
        t3::RenderSystem::BufferUsage::DYNAMIC_DRAW
    );
    
    RenderSystem::bindBuffer(
        t3::RenderSystem::BufferType::TYPE_INDEX,
        index_buffer_
    );
    RenderSystem::setupBufferData(
        t3::RenderSystem::BufferType::TYPE_INDEX,
        static_cast<int>(indices.size() * sizeof(uint32_t)),
        indices.data(),
        t3::RenderSystem::BufferUsage::DYNAMIC_DRAW
    );
    

}

void SpriteRenderer::renderSprites() {

    //  テクスチャの割り当て
    const std::shared_ptr<Texture>& texture = sprites_[0]->getTexture();
    texture->setupTexture();

    sprite_shader_.setAttributePointer(
        "position",
        2,
        sizeof(VertexP2T),
        0
    );

    sprite_shader_.setAttributePointer(
        "uv",
        2,
        sizeof(VertexP2T),
        (void*)(sizeof(float) * 2)
    );
    
    // 描画
    RenderSystem::drawElements(
        RenderSystem::DrawMode::MODE_TRIANGLE_STRIP,
        draw_count_,
        sizeof(uint32_t)
    );


}


void SpriteRenderer::endRender()
{
    //  設定の後片付け
    

    
    //  描画設定解除
    t3::RenderSystem::setTextureMapping(false);
    t3::RenderSystem::setBlend(false);

    //  描画コンテナのクリア
    sprites_.clear();
}



}   // inline namespace gfx
}   // namespace t3











