
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
    bool operator()(const t3::Sprite* x, const t3::Sprite* y) const {
        return x->getPriority() > y->getPriority();
    }
};


  
}

namespace t3 {
inline namespace gfx {

SpriteRenderer::SpriteRenderer()
    : vertex_buffer_()
    , index_buffer_()
{

    VertexP2T v[4] =
    {  // x, y,  tu,   tv
        {  0, 0, 0.0f, 0.0f },
        {  1, 0, 1.0f, 0.0f },
        {  1, 1, 1.0f, 1.0f },
        {  0, 1, 0.0f, 1.0f },
    };
    

    std::vector<float> vertices;
    for (int i = 0; i < 4; ++i) {
        vertices.push_back(v[i].x);
        vertices.push_back(v[i].y);
        vertices.push_back(v[i].u);
        vertices.push_back(v[i].v);
    }
    
    std::vector<uint32_t> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    
    vertex_buffer_ = RenderSystem::createVertexBuffer(vertices);
    index_buffer_ = RenderSystem::createIndexBuffer(indices);
    
    
    sprite_render_shader_ = RenderSystem::buildProgram(sprite_vsh, sprite_fsh);
    sv_pos_ = RenderSystem::getUniformLocation(sprite_render_shader_, "Position");
    sv_uv_ = RenderSystem::getUniformLocation(sprite_render_shader_, "TextureCoord");
    
    //  スプライトコンテナのメモリを事前に確保
    sprites_.reserve(256);
}


SpriteRenderer::~SpriteRenderer()
{
}



void SpriteRenderer::collectSprite(
    const t3::Sprite& sprite 
){
    sprites_.push_back( &sprite );
}


void SpriteRenderer::beginRender()
{
    //  スプライトのソート
    std::sort(sprites_.begin(), sprites_.end(), PriorityCompare());
    
    
    //  レンダリング設定
    const t3::GameSystem* gs = t3::GameSystem::getInstancePointer();
    const t3::Point2& screen_size = gs->getScreenSize();
    
    
    //頂点配列を有効化
    RenderSystem::bindBuffer(
        RenderSystem::BufferType::TYPE_VERTEX,
        vertex_buffer_
    );
    RenderSystem::setVertexAttribute(
        sv_pos_,
        2,
        sizeof(VertexP2T),
        0
    );
    RenderSystem::setVertexAttribute(
        sv_uv_,
        2,
        sizeof(VertexP2T),
        2
    );
    RenderSystem::bindBuffer(RenderSystem::BufferType::TYPE_INDEX, index_buffer_);

    
    //頂点構造体内の頂点座標、頂点色のオフセットを指定

    //  正射影行列を設定
    Mtx4 projection;
    float w = screen_size.x_;
    float h = screen_size.y_;
    projection.ortho(0, w, h, 0, -1.0f, 1.0f);
    t3::RenderSystem::setProjectionMatrix(projection);

        
    t3::RenderSystem::setTextureMinFilter(
        t3::RenderSystem::TextureFilterType::TYPE_NEAREST
    );
    t3::RenderSystem::setTextureMagFilter(
        t3::RenderSystem::TextureFilterType::TYPE_NEAREST
    );
    t3::RenderSystem::setBlendFunctionType(
        t3::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        t3::RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
    );
    
    t3::RenderSystem::setTextureMapping(true);
    t3::RenderSystem::setBlend(true);


}


void SpriteRenderer::render()
{
    //  レンダリング設定
    beginRender();

    for (auto& sprite : sprites_){
        //  座標情報など設定
        // モデルビュー変換行列を設定する
        const Vec2& pos = sprite->getPosition();
        const Vec2& scale = sprite->getSize();
        
        Mtx4 trans_mtx;
        Mtx4 scale_mtx;
        trans_mtx.translate( pos.x_, pos.y_, 0 );
        scale_mtx.scale( scale.x_, scale.y_, 1 );

        Mtx4 modelview = scale_mtx * trans_mtx;
        t3::RenderSystem::setWorldTransformMatrix(modelview);

        //  テクスチャの割り当て
        const std::shared_ptr<Texture>& texture = sprite->getTexture();
        t3::RenderSystem::setTexture(texture);
 
        // 描画
        RenderSystem::drawElements(
            RenderSystem::DrawMode::MODE_QUADS,
            4,
            sizeof(short)
        );
    }
    
    endRender();
}


void SpriteRenderer::endRender()
{
    //  設定の後片付け
    

    //頂点配列を有効化
    RenderSystem::setVertexArrayUse(false);
    RenderSystem::setColorArrayUse(false);
    RenderSystem::setTexCoordArrayUse(false);

    
    //  描画設定解除
    t3::RenderSystem::setTextureMapping(false);
    t3::RenderSystem::setBlend(false);

    //  描画コンテナのクリア
    sprites_.clear();
}



}   // inline namespace gfx
}   // namespace t3











