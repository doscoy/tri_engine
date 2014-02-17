
#include "tri_sprite_renderer.hpp"
#include "tri_sprite.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_index_buffer.hpp"
#include "tri_vertex_types.hpp"
#include "base/tri_game_system.hpp"
#include "tri_texture.hpp"
#include "math/tri_matrix.hpp"
#include "gfx/tri_render_system.hpp"
#include <algorithm>



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
    : vertex_buffer_( nullptr )
    , index_buffer_( nullptr )
{

    VertexP2CT v[4] =
    {   // x,   y,   r,   g,   b,   a,   tu,   tv
        {  0, 0, 255, 255, 255, 255, 0.0f, 0.0f },
        {  1, 0, 255, 255, 255, 255, 1.0f, 0.0f },
        {  1, 1, 255, 255, 255, 255, 1.0f, 1.0f },
        {  0, 1, 255, 255, 255, 255, 0.0f, 1.0f },
    };
    
    GLushort i[4] = {
        0, 1, 2, 3,
    };

    vertex_buffer_.reset( T3_NEW VertexBuffer<VertexP2CT>( 4, v ) );
    index_buffer_.reset( T3_NEW IndexBuffer( 4, i ) );
    
    //  スプライトコンテナのメモリを事前に確保
    sprites_.reserve( 256 );
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
    RenderSystem::setVertexArrayUse(true);
    RenderSystem::setColorArrayUse(true);
    RenderSystem::setTexCoordArrayUse(true);

    vertex_buffer_->bindBuffer();
    index_buffer_->bindBuffer();
    
    //頂点構造体内の頂点座標、頂点色のオフセットを指定
    
    
    t3::RenderSystem::setVertexPointer(2, sizeof(VertexP2CT), 0);
    
    
    t3::RenderSystem::setColorPointer(
        4, 
        sizeof(VertexP2CT),
        reinterpret_cast<GLvoid*>(sizeof(VertexP2CT::position_t) * 2)
    );
    
    t3::RenderSystem::setTexCoordPointer(
        2, 
        sizeof(VertexP2CT),
        reinterpret_cast<GLvoid*>((sizeof(VertexP2CT::position_t) * 2) + (sizeof( VertexP2CT::color8_t ) * 4))
    );

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
    //バッファオブジェクトのバインド解除
    vertex_buffer_->unbindBuffer();
    index_buffer_->unbindBuffer();
    

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











