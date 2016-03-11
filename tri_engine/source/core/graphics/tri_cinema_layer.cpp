////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/tri_cinema_layer.hpp"
#include "shader/tri_simple_tex.fsh"
#include "shader/tri_simple_tex.vsh"
#include "shader/tri_show_depth_tex.fsh"
#include "core/graphics/tri_vertex_types.hpp"


TRI_CORE_NS_BEGIN

  

///
/// コンストラクタ
CinemaLayer::CinemaLayer()
    : CinemaLayer(Position2D(-1,-1), Position2D(1,1))
{}

///
/// コンストラクタ
CinemaLayer::CinemaLayer(
    const Position2D min_pos,
    const Position2D max_pos,
    const String& name,
    const Priority priority
)   : LayerBase(name, priority)
    , vao_()
    , vb_()
    , ib_()
    , shader_(nullptr)
    , color_shader_(nullptr)
    , depth_shader_(nullptr)
    , texture_(nullptr)
{

    
    //  VAO用意
    vao_ = cross::RenderSystem::createVertexArrayObject();
    cross::RenderSystem::bindVertexArrayObject(vao_);

    //  VertexBuffer登録
    vb_.bind();

    VertexP2T varray[4];
    varray[0].position_ = min_pos;
    varray[0].uv_ = t3::Vec2(0,0);

    varray[1].position_ = Position2D(max_pos.x_, min_pos.y_);
    varray[1].uv_ = t3::Vec2(1,0);

    varray[2].position_ = Position2D(min_pos.x_, max_pos.y_);
    varray[2].uv_ = t3::Vec2(0,1);

    varray[3].position_ = max_pos;
    varray[3].uv_ = t3::Vec2(1,1);
    
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_VERTEX,
        sizeof(VertexP2T) * 4,
        varray,
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );
    
    //  IndexBuffer登録
    ib_.bind();
    uint32_t iarray[] = {0,1,2,3};
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_INDEX,
        sizeof(uint32_t) * 4,
        iarray,
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );
    
    
    //  デフォルトのカラーシェーダ作成
    //  テクスチャのカラー値を表示するシェーダ
    color_shader_ = Shader::create(simple_tex_vsh, simple_tex_fsh);
    
    //  デフォルトのデプスシェーダ作成
    //  テクスチャのデプス値を表示するシェーダ
    depth_shader_ = Shader::create(simple_tex_vsh, show_depth_tex_fsh);
    
    //  デフォルトシェーダを設定
    useDefaultColorShader();


    
    
    constexpr int POSITION_SLOT = 0;
    constexpr int UV_SLOT = 1;


    //  座標有効化
    cross::RenderSystem::setEnableVertexAttribute(POSITION_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        POSITION_SLOT,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VertexP2T),
        0
    );


    //  UV有効化
    cross::RenderSystem::setEnableVertexAttribute(UV_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        UV_SLOT,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VertexP2T),
        (void*)offsetof(VertexP2T, uv_)
    );


    cross::RenderSystem::bindVertexArrayObject(0);
}


CinemaLayer::~CinemaLayer() {
    cross::RenderSystem::deleteVertexArrayBuffer(vao_);
}


void CinemaLayer::updateLayer(const DeltaTime delta_time) {


}


void CinemaLayer::renderLayer() {
    
    if (!texture_) {
        return;
    }
    
    cross::RenderSystem::resetBufferBind();
    cross::RenderSystem::bindVertexArrayObject(vao_);
    
    cross::RenderSystem::setCulling(false);
    cross::RenderSystem::setDepthTest(false);


    // シェーダで描画
    bool use_result = shader_->use();
    T3_ASSERT(use_result);
    

    //頂点配列を有効化
    shader_->bindAttributeLocation(0, "a_position");
    shader_->bindAttributeLocation(1, "a_uv");
    shader_->bindFragmentDataLocation(0, "FragColor");

    shader_->setUniform("sampler", 0);
    cross::RenderSystem::setActiveTextureUnit(0);
    texture_->bind();
    
    
    cross::RenderSystem::drawElements(
        cross::RenderSystem::DrawMode::MODE_TRIANGLE_STRIP,
        4,
        sizeof(uint32_t)
    );
    cross::RenderSystem::bindVertexArrayObject(0);

}



TRI_CORE_NS_END
