
#include "tri_sprite_renderer.hpp"
#include "tri_sprite.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_index_buffer.hpp"
#include "tri_vertex_types.hpp"
#include "../kernel/tri_game_system.hpp"
#include "tri_texture.hpp"
#include "../math/tri_matrix.hpp"
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
    {   //     x,      y,   r,   g,   b,   a,   tu,   tv
        { 0, 0, 255, 255, 255, 255, 0.0f, 0.0f },
        { 1, 0, 255, 255, 255, 255, 1.0f, 0.0f },
        { 1, 1, 255, 255, 255, 255, 1.0f, 1.0f },
        { 0, 1, 255, 255, 255, 255, 0.0f, 1.0f },
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
    const t3::ivec2_t& screen_size = gs->getScreenSize();
    float w = screen_size.x;
    float h = screen_size.y;

    
    //頂点配列を有効化
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );

    vertex_buffer_->bind( true );
    index_buffer_->bind( true );
    
    //頂点構造体内の頂点座標、頂点色のオフセットを指定
    glVertexPointer( 
        2,
        GL_FLOAT,
        sizeof( VertexP2CT ),
        reinterpret_cast< GLvoid* >( 0 ) 
    );
    
    glColorPointer( 
        4, 
        GL_UNSIGNED_BYTE, 
        sizeof( VertexP2CT ),
        reinterpret_cast< GLvoid* >( sizeof( VertexP2CT::position_t ) * 2 ) 
    );
    
    glTexCoordPointer( 
        2, 
        GL_FLOAT, 
        sizeof( VertexP2CT ), 
        reinterpret_cast< GLvoid* >( (sizeof( VertexP2CT::position_t ) * 2)+(sizeof( VertexP2CT::color_t ) * 4) )
    );

    //  正射影行列を設定
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    mtx4_t projection;
    projection.ortho(0, w, h, 0, -1.0f, 1.0f);
    glLoadMatrixf( projection.pointer() );


    //  テクスチャ画像はバイト単位に詰め込まれている
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

}


void SpriteRenderer::render()
{
    //  レンダリング設定
    beginRender();

    for ( auto sprite : sprites_ ){
        //  座標情報など設定
        // モデルビュー変換行列を設定する
        const vec2_t& pos = sprite->getPosition();
        const vec2_t& scale = sprite->getSize();
        
        mtx4_t trans_mtx;
        mtx4_t scale_mtx;
        trans_mtx.translate( pos.x, pos.y, 0 );
        scale_mtx.scale( scale.x, scale.y, 1 );

        glMatrixMode(GL_MODELVIEW);
        mtx4_t modelview = scale_mtx * trans_mtx;
        glLoadMatrixf( modelview.pointer() );
        

        //  テクスチャの割り当て
        const Texture* texture = sprite->getTexture();
        glTexImage2D(
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
        glDrawElements( GL_QUADS, 4, GL_UNSIGNED_SHORT, nullptr );
        
        
    }
    
    endRender();
}


void SpriteRenderer::endRender()
{
    //  設定の後片付け
    //バッファオブジェクトのバインド解除
    vertex_buffer_->bind( false );
    index_buffer_->bind( false );
    
    //頂点配列を無効化
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    
    //  描画設定解除
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    
    //  描画コンテナのクリア
    sprites_.clear();
}



}   // inline namespace gfx
}   // namespace t3











