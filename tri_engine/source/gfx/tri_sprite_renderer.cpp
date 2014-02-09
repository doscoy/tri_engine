
#include "tri_sprite_renderer.hpp"
#include "tri_sprite.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_index_buffer.hpp"
#include "tri_vertex_types.hpp"
#include "base/tri_game_system.hpp"
#include "tri_texture.hpp"
#include "math/tri_matrix.hpp"
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
    std::sort( sprites_.begin(), sprites_.end(), PriorityCompare() );
    
    
    //  レンダリング設定
    const t3::GameSystem* gs = t3::GameSystem::getInstancePointer();
    const t3::Point2& screen_size = gs->getScreenSize();
    float w = screen_size.x_;
    float h = screen_size.y_;

    
    //頂点配列を有効化
    ogl::enableClientState( GL_VERTEX_ARRAY );
    ogl::enableClientState( GL_COLOR_ARRAY );
    ogl::enableClientState( GL_TEXTURE_COORD_ARRAY );

    vertex_buffer_->bindBuffer();
    index_buffer_->bindBuffer();
    
    //頂点構造体内の頂点座標、頂点色のオフセットを指定
    ogl::vertexPointer( 
        2,
        GL_FLOAT,
        sizeof( VertexP2CT ),
        reinterpret_cast< GLvoid* >( 0 ) 
    );
    
    ogl::colorPointer(
        4, 
        GL_UNSIGNED_BYTE, 
        sizeof( VertexP2CT ),
        reinterpret_cast< GLvoid* >( sizeof( VertexP2CT::position_t ) * 2 ) 
    );
    
    ogl::texCoordPointer(
        2, 
        GL_FLOAT, 
        sizeof( VertexP2CT ), 
        reinterpret_cast< GLvoid* >( (sizeof( VertexP2CT::position_t ) * 2)+(sizeof( VertexP2CT::color8_t ) * 4) )
    );

    //  正射影行列を設定
    ogl::matrixMode(GL_PROJECTION);
    ogl::pushMatrix();
    ogl::loadIdentity();
    Mtx4 projection;
    projection.ortho(0, w, h, 0, -1.0f, 1.0f);
    ogl::loadMatrixf( projection.pointer() );


    //  テクスチャ画像はバイト単位に詰め込まれている
    ogl::pixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        
    ogl::texParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ogl::texParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    ogl::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ogl::enable(GL_TEXTURE_2D);
    ogl::enable(GL_BLEND);

}


void SpriteRenderer::render()
{
    //  レンダリング設定
    beginRender();

    for ( auto sprite : sprites_ ){
        //  座標情報など設定
        // モデルビュー変換行列を設定する
        const Vec2& pos = sprite->getPosition();
        const Vec2& scale = sprite->getSize();
        
        Mtx4 trans_mtx;
        Mtx4 scale_mtx;
        trans_mtx.translate( pos.x_, pos.y_, 0 );
        scale_mtx.scale( scale.x_, scale.y_, 1 );

        ogl::matrixMode(GL_MODELVIEW);
        Mtx4 modelview = scale_mtx * trans_mtx;
        ogl::loadMatrixf( modelview.pointer() );
        

        //  テクスチャの割り当て
        const Texture* texture = sprite->getTexture();
        ogl::texImage2d(
            GL_TEXTURE_2D, 
            0, 
            texture->getColorFormat(),
            texture->getWidth(),
            texture->getHeight(),
            0,
            texture->getColorFormat(),
            GL_UNSIGNED_BYTE,
            texture->getData()
        );
 
        // 描画
        
        ogl::drawElements(
            GL_QUADS,
            4,
            GL_UNSIGNED_SHORT,
            0
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
    
    //頂点配列を無効化
    ogl::disableClientState( GL_VERTEX_ARRAY );
    ogl::disableClientState( GL_COLOR_ARRAY );
    ogl::disableClientState( GL_TEXTURE_COORD_ARRAY );
    
    //  描画設定解除
    ogl::disable( GL_TEXTURE_2D );
    ogl::disable( GL_BLEND );
    
    //  描画コンテナのクリア
    sprites_.clear();
}



}   // inline namespace gfx
}   // namespace t3











