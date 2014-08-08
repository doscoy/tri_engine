
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


#define SHADER_ATTR_POSITION        "a_position"
#define SHADER_ATTR_UV              "a_uv"
#define SHADER_ATTR_COLOR           "a_color"


namespace {

class PriorityCompare
{
public:
    bool operator()(const t3::SpritePtr lhs, const t3::SpritePtr rhs) const {
        return lhs->sortScore() < rhs->sortScore();
    }
};


  
}

namespace t3 {
inline namespace gfx {

SpriteRenderer::SpriteRenderer()
    : sprites_()
    , shader_(nullptr)
    , default_shader_(nullptr)
{
    default_shader_ = std::make_shared<Shader>();

    default_shader_->compileShaderFromString(
        sprite_vsh,
        RenderSystem::ShaderType::VERTEX_SHADER
    );
    default_shader_->compileShaderFromString(
        sprite_fsh,
        RenderSystem::ShaderType::FRAGMENT_SHADER
    );
    bool link_result = default_shader_->link();
    T3_ASSERT(link_result);
    
    useDefaultShader();
    
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
    T3_NULL_ASSERT(shader_);
    bool use_result = shader_->use();
    T3_ASSERT(use_result);
    //  スプライトのソート
    std::sort(sprites_.begin(), sprites_.end(), PriorityCompare());

    shader_->setEnableAttributeArray(SHADER_ATTR_POSITION, true);
    shader_->setEnableAttributeArray(SHADER_ATTR_COLOR, true);
    shader_->setEnableAttributeArray(SHADER_ATTR_UV, true );
    
    //頂点配列を有効化
    shader_->setUniform("sampler", 0);
    

    RenderSystem::setActiveTextureUnit(RenderSystem::TextureUnit::UNIT0);

    t3::RenderSystem::setBlendFunctionType(
        t3::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        t3::RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
    );

    t3::RenderSystem::setBlend(true);
    t3::RenderSystem::setCulling(false);

}


void SpriteRenderer::margeSprites() {

    std::vector<VertexP2CT> vertices;
    std::vector<uint32_t> indices;
    
    vertices.reserve(sprites_.size() * 16);
    indices.reserve(sprites_.size() * 6);


    Vec2 screen_size = Director::instance().virtualScreenSize();
    Vec2 half = screen_size / 2;
    half.x_ = 1.0f / half.x_;
    half.y_ = 1.0f / half.y_;
    
    for (int i = 0; i < sprites_.size(); ++i) {
        auto spr = sprites_[i];
    
        const Vec2& pivot = spr->pivot();
        const Vec2& size = spr->size();
        
        //  初期配置
        Vec2 lt = Vec2(      0 - pivot.x_, size.y_ - pivot.y_);
        Vec2 lb = Vec2(      0 - pivot.x_, 0 - pivot.y_);
        Vec2 rt = Vec2(size.x_ - pivot.x_, size.y_ - pivot.y_);
        Vec2 rb = Vec2(size.x_ - pivot.x_, 0 - pivot.y_);
        
        //  スケーリング
        if (spr->isScaledSprite()) {
            const Vec2& scale = spr->transform()->scale();
            lt *= scale;
            lb *= scale;
            rt *= scale;
            rb *= scale;
        }

        //  回転
        if (spr->isRotatedSprite()) {
            float angle = toRadian(spr->transform()->globalRotation());

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
            const Vec2& pos =spr->transform()->globalPosition();

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
        const texture_coord_t& uv = spr->textureCoord();
        const Color& color = spr->color();
        {
            VertexP2CT v1;
            v1.x_ = lt.x_;
            v1.y_ = lt.y_;
            v1.r_ = color.red_;
            v1.g_ = color.green_;
            v1.b_ = color.blue_;
            v1.a_ = color.alpha_;
            v1.tu_ = uv.u0_;
            v1.tv_ = uv.v0_;
            vertices.push_back(v1);
        }

        {
            VertexP2CT v2;
            v2.x_ = lb.x_;
            v2.y_ = lb.y_;
            v2.r_ = color.red_;
            v2.g_ = color.green_;
            v2.b_ = color.blue_;
            v2.a_ = color.alpha_;
            v2.tu_ = uv.u0_;
            v2.tv_ = uv.v1_;
            vertices.push_back(v2);
        }


        {
            VertexP2CT v3;
            v3.x_ = rt.x_;
            v3.y_ = rt.y_;
            v3.r_ = color.red_;
            v3.g_ = color.green_;
            v3.b_ = color.blue_;
            v3.a_ = color.alpha_;
            v3.tu_ = uv.u1_;
            v3.tv_ = uv.v0_;
            vertices.push_back(v3);
        }
        
 
       {
            VertexP2CT v4;
            v4.x_ = rb.x_;
            v4.y_ = rb.y_;
            v4.r_ = color.red_;
            v4.g_ = color.green_;
            v4.b_ = color.blue_;
            v4.a_ = color.alpha_;
            v4.tu_ = uv.u1_;
            v4.tv_ = uv.v1_;
            vertices.push_back(v4);
        }
        
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
    
    //  頂点バッファ更新
    RenderSystem::bindBuffer(
        t3::RenderSystem::BufferType::TYPE_VERTEX,
        vertex_buffer_
    );
    RenderSystem::setupBufferData(
        t3::RenderSystem::BufferType::TYPE_VERTEX,
        static_cast<int>(vertices.size() * sizeof(VertexP2CT)),
        vertices.data(),
        t3::RenderSystem::BufferUsage::DYNAMIC_DRAW
    );
    
    //  インデックスバッファ更新
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
    const std::shared_ptr<Texture>& texture = sprites_[0]->texture();
    texture->setupTexture();

    shader_->setAttributePointer(
        SHADER_ATTR_POSITION,
        2,
        GL_FLOAT,
        false,
        sizeof(VertexP2CT),
        0
    );

    shader_->setAttributePointer(
        SHADER_ATTR_COLOR,
        4,
        GL_UNSIGNED_BYTE,
        true,
        sizeof(VertexP2CT),
        (void*)(sizeof(float) * 2)
    );
    
    shader_->setAttributePointer(
        SHADER_ATTR_UV,
        2,
        GL_FLOAT,
        false,
        sizeof(VertexP2CT),
        (void*)(sizeof(float) * 3)
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
    t3::RenderSystem::setBlend(false);

    //  描画コンテナのクリア
    sprites_.clear();
}



}   // inline namespace gfx
}   // namespace t3











