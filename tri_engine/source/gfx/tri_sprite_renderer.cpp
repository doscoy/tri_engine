
#include "tri_sprite_renderer.hpp"
#include "tri_sprite.hpp"
#include "tri_vertex_types.hpp"
#include "base/tri_game_system.hpp"
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
    bool operator()(const t3::Sprite* lhs, const t3::Sprite* rhs) const {
        return lhs->getSortScore() > rhs->getSortScore();
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
    t3::Sprite& sprite 
){
    sprites_.push_back( &sprite );
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
    std::sort(sprites_.begin(), sprites_.end(), PriorityCompare());

    sprite_shader_.setEnableAttributeArray("position", true);
    sprite_shader_.setEnableAttributeArray("uv", true );
    
    
    //  レンダリング設定
    const t3::GameSystem* gs = t3::GameSystem::getInstancePointer();
    const t3::Point2& screen_size = gs->getScreenSize();
    
    
    //頂点配列を有効化
    sprite_shader_.setUniform("sampler", 0);
    
    //  正射影行列を設定
    Mtx4 projection;
    float w = screen_size.x_ / 2;
    float h = screen_size.y_ / 2;
//    projection.ortho(-w, w, -h, h, -1.0f, 1.0f);
//    sprite_shader_.setUniform("projection", projection);

    RenderSystem::setActiveTextureUnit(RenderSystem::TextureUnit::UNIT0);

    t3::RenderSystem::setBlendFunctionType(
        t3::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        t3::RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
    );

    t3::RenderSystem::setTextureMapping(true);
    t3::RenderSystem::setBlend(true);
    t3::RenderSystem::setCulling(false);


}

void SpriteRenderer::renderSprite(
    Sprite& sprite
) {
/*
    //  座標情報など設定
    // モデルビュー変換行列を設定する
    const Mtx4* mtx = sprite.getMatrix();
    sprite_shader_.setUniform("transform", *mtx);
    //  テクスチャの割り当て
    const std::shared_ptr<Texture>& texture = sprite.getTexture();
    texture->setupTexture();
    
    
    //  頂点バッファ設定
    RenderSystem::bindBuffer(
        RenderSystem::BufferType::TYPE_VERTEX,
        sprite.getVertexBuffer()
    );
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
    RenderSystem::bindBuffer(
        RenderSystem::BufferType::TYPE_INDEX,
        sprite.getIndexBuffer()
    );
    // 描画
    RenderSystem::drawElements(
        RenderSystem::DrawMode::MODE_TRIANGLE_STRIP,
        4,
        sizeof(uint32_t)
    );
*/
}


void SpriteRenderer::margeSprites() {

    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    
    vertices.reserve(sprites_.size() * 16);
    indices.reserve(sprites_.size() * 6);


    Vec2 screen_size = GameSystem::getInstance().getScreenSize();
    Vec2 half = screen_size / 2;
    half.x_ = 1.0f / half.x_;
    half.y_ = 1.0f / half.y_;
    
    for (int i = 0; i < sprites_.size(); ++i) {
        auto spr = sprites_[i];
    
        const Vec2& pos =spr->getPosition();
        const Vec2& pivot = spr->getPivot();
        const Vec2& size = spr->getSize();
        const Vec2& scale = spr->getScale();
        const texture_coord_t& uv = spr->getTextureCoord();

        //  初期配置
        Vec2 lt = Vec2(size.x_ - pivot.x_, size.y_ + pivot.y_);
        Vec2 lb = Vec2(size.x_ - pivot.x_, size.y_ - pivot.y_);
        Vec2 rt = Vec2(size.x_ + pivot.x_, size.y_ + pivot.y_);
        Vec2 rb = Vec2(size.x_ + pivot.x_, size.y_ - pivot.y_);
        
        //  スケーリング
        lt *= scale;
        lb *= scale;
        rt *= scale;
        rb *= scale;


        //  位置移動
        lt += pos;
        lb += pos;
        rt += pos;
        rb += pos;
        
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

        //  インデックスはバッファ
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
    draw_count_ = indices.size();
    
    //  バッファ更新
    RenderSystem::bindBuffer(
        t3::RenderSystem::BufferType::TYPE_VERTEX,
        vertex_buffer_
    );
    RenderSystem::setupBufferData(
        t3::RenderSystem::BufferType::TYPE_VERTEX,
        vertices.size() * sizeof(float),
        vertices.data(),
        t3::RenderSystem::BufferUsage::DYNAMIC_DRAW
    );
    
    RenderSystem::bindBuffer(
        t3::RenderSystem::BufferType::TYPE_INDEX,
        index_buffer_
    );
    RenderSystem::setupBufferData(
        t3::RenderSystem::BufferType::TYPE_INDEX,
        indices.size() * sizeof(uint32_t),
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











