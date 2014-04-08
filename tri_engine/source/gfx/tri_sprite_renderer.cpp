
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
    sprites_.reserve(256);
}
    

SpriteRenderer::~SpriteRenderer()
{
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

    for (Sprite* sprite : sprites_){
        renderSprite(*sprite);
    }
    
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
    projection.ortho(-w, w, -h, h, -1.0f, 1.0f);
    sprite_shader_.setUniform("projection", projection);

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











