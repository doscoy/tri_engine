
#include "tri_sprite.hpp"
#include "base/tri_game_system.hpp"
#include "gfx/tri_resource_manager.hpp"
#include "tri_sprite_layer.hpp"
#include "tri_vertex_types.hpp"




namespace t3 {
inline namespace gfx {

// *********************************************
//  コンストラクタ
Sprite::Sprite()
    : texture_( nullptr )
    , position_( 0, 0 )
    , size_( 0, 0 )
    , pivot_( 0, 0 )
    , rotation_( 0, 0, 0 )
    , texture_coord_{ 0, 0, 1, 1 }
    , scale_( 1.0f, 1.0f )
    , priority_( PRIORITY_NORMAL )
    , enable_( true )
    , owner_( nullptr )
    , calc_matrix_request_(true)
    , matrix_()
    , vertex_buffer_(0)
    , index_buffer_(0)
{
    std::vector<uint32_t> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    index_buffer_ = RenderSystem::createIndexBuffer(indices);

}


// *********************************************
//  デストラクタ
Sprite::~Sprite()
{
}


// *********************************************
//  テクスチャ設定
void Sprite::setTexture(
    std::shared_ptr<Texture> tex
){
    texture_ = tex;
    T3_NULL_ASSERT( texture_ );
    
    
    float tex_width = tex->getWidth();
    float tex_height = tex->getHeight();
    
    setPivot(Vec2(tex_width * 0.5f, tex_height * 0.5f));

    setSize(Vec2(tex_width, tex_height));
    
}

void Sprite::setupVertexBuffer() {
    
    float size_x = size_.x_;
    float size_y = size_.y_;
    
    float u0 = texture_coord_.u0_;
    float u1 = texture_coord_.u1_;
    float v0 = texture_coord_.v0_;
    float v1 = texture_coord_.v1_;
    
    VertexP2T v[4] =
    { //      x,      y, tu, tv
        {  0.0f,   0.0f, u0, v0},
        {  0.0f, size_y, u0, v1},
        {size_x,   0.0f, u1, v0},
        {size_x, size_y, u1, v1},
    };
    
    
    std::vector<float> vertices;
    for (int i = 0; i < 4; ++i) {
        vertices.push_back(v[i].x);
        vertices.push_back(v[i].y);
        vertices.push_back(v[i].u);
        vertices.push_back(v[i].v);
    }
    
    if (vertex_buffer_ != 0){
        RenderSystem::deleteBuffer(&vertex_buffer_);
    }
    vertex_buffer_ = RenderSystem::createVertexBuffer(vertices);

}


void Sprite::attachToLayer( SpriteLayer* const layer )
{
    owner_ = layer;
    owner_->attachSprite( this );
}

void Sprite::detachToLayer()
{
    T3_NULL_ASSERT( owner_ );
    owner_->detachSprite( this );
    owner_ = nullptr;
}


void Sprite::destroy()
{
    detachToLayer();
    delete this;
}


bool Sprite::isValid() const
{
    if ( !owner_ ){
        return false;
    }
    

    return true;
}

int Sprite::getSortScore() const {
    int score = getPriority();
    return score;
}



const Mtx4* Sprite::getMatrix() {
    
    if (calc_matrix_request_) {
        calc_matrix_request_ = false;
        calcMatrix();
    }
    

    return &matrix_;
}

void Sprite::calcMatrix() {
    
    
    Mtx4 pivot_mtx;
    pivot_mtx.translate(-pivot_.x_, -pivot_.y_, 0);
    
    Mtx4 trans_mtx;
    trans_mtx.translate(position_.x_, position_.y_, 0);
    
    Mtx4 rot_mtx;
    rot_mtx.rotate(rotation_);
    
    Mtx4 scale_mtx;
    scale_mtx.scale(scale_.x_, scale_.y_, 1);
    
     matrix_ = pivot_mtx * scale_mtx * rot_mtx * trans_mtx;
    
    
    
}







}   // inline namespace gfx
}   // namespace t3

