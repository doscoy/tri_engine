
#include "gfx/tri_sprite_renderer.hpp"
#include "gfx/tri_sprite.hpp"
#include "base/tri_director.hpp"
#include "gfx/tri_texture.hpp"
#include "math/tri_matrix.hpp"

#include <algorithm>


#include "../shader/tri_sprite.vsh"
#include "../shader/tri_sprite.fsh"


#define SHADER_ATTR_POSITION        "a_position"
#define SHADER_ATTR_UV              "a_uv"
#define SHADER_ATTR_COLOR           "a_color"

#define USE_VAO 1
#define USE_GLMAP 1


namespace {

class PriorityCompare
{
public:
    bool operator()(const t3::SpritePtr lhs, const t3::SpritePtr rhs) const {
        int lhs_score = lhs->sortScore();
        int rhs_score = rhs->sortScore();
        
        if (lhs_score != rhs_score) {
            //  ソートスコアに差がある場合は単純にスコアで比較
            return lhs_score < rhs_score;
        }
        
        //  ソートスコアが同じ場合はバッチ範囲が広くなるように同じテクスチャが
        //  連続するようにスコアを出す
        return lhs->texture()->resourceID() > rhs->texture()->resourceID();
    }
};


  
}

namespace t3 {

SpriteRenderer::SpriteRenderer()
    : sprites_()
    , shader_(nullptr)
    , default_shader_(nullptr)
    , batch_groups_()
    , current_batch_idx_(-1)
{
    //  デフォルトのシェーダ準備
    default_shader_ = std::make_shared<Shader>();

    default_shader_->build(sprite_vsh, sprite_fsh);
    
    //  デフォルトのシェーダを使う
    useDefaultShader();
    
    //  スプライトコンテナのメモリを事前に確保
    sprites_.reserve(4096);
    
    
    //  バッチグループの初期化
#ifdef USE_VAO
    for (auto& group : batch_groups_) {
        group.bindVAO();
        group.vertexBuffer().bind();

         //  設定の後片付け

        shader_->setAttributePointer(
            SHADER_ATTR_POSITION,
            2,
            cross::RenderSystem::FLOAT,
            false,
            sizeof(VertexP2CT),
            (void*)offsetof(VertexP2CT, x_)
        );

        shader_->setAttributePointer(
            SHADER_ATTR_COLOR,
            4,
            cross::RenderSystem::BYTE,
            true,
            sizeof(VertexP2CT),
            (void*)offsetof(VertexP2CT, r_)
        );
        
        shader_->setAttributePointer(
            SHADER_ATTR_UV,
            2,
            cross::RenderSystem::FLOAT,
            false,
            sizeof(VertexP2CT),
            (void*)offsetof(VertexP2CT, tu_)
        );

        shader_->setEnableAttributeArray(SHADER_ATTR_POSITION, true);
        shader_->setEnableAttributeArray(SHADER_ATTR_COLOR, true);
        shader_->setEnableAttributeArray(SHADER_ATTR_UV, true);

        cross::RenderSystem::setupBufferData(
            cross::RenderSystem::BufferType::TYPE_VERTEX,
            sizeof(VertexP2CT) * 4096 * 4,
            nullptr,
            cross::RenderSystem::BufferUsage::DYNAMIC_DRAW
        );
        
        group.indexBuffer().bind();
        cross::RenderSystem::setupBufferData(
            cross::RenderSystem::BufferType::TYPE_INDEX,
            sizeof(uint32_t) * 4096 * 4 * 2,
            nullptr,
            cross::RenderSystem::BufferUsage::DYNAMIC_DRAW
        );

    }
    cross::RenderSystem::bindVertexArrayBuffer(0);
#endif
}
    

SpriteRenderer::~SpriteRenderer()
{


}



void SpriteRenderer::collectSprite(
    SpritePtr sprite
) {
    sprites_.push_back(sprite);
}





void SpriteRenderer::render() {

    if (sprites_.empty()) {
        //  描画すべきスプライトが無い場合は即終了
        return;
    }

    //  レンダリング設定
    beginRender();
    
    for (int i = 0; i <= current_batch_idx_; ++i) {
        renderBatch(&batch_groups_[i]);
    }
    
    endRender();
    
}

void SpriteRenderer::beginRender() {


    T3_NULL_ASSERT(shader_);
    bool use_result = shader_->use();
    T3_ASSERT(use_result);

#ifndef USE_VAO
    shader_->setEnableAttributeArray(SHADER_ATTR_POSITION, true);
    shader_->setEnableAttributeArray(SHADER_ATTR_COLOR, true);
    shader_->setEnableAttributeArray(SHADER_ATTR_UV, true );
#endif
    //頂点配列を有効化
    shader_->setUniform("sampler", 0);
    

    cross::RenderSystem::setActiveTextureUnit(
        cross::RenderSystem::TextureUnit::UNIT0
    );

    cross::RenderSystem::setBlend(true);
    cross::RenderSystem::setCulling(false);
    cross::RenderSystem::setDepthTest(false);
    cross::RenderSystem::setDepthWrite(false);


    cross::RenderSystem::setBlendFunctionType(
        cross::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        cross::RenderSystem::BlendFunctionType::TYPE_ONE
    );

}
    

SpriteRenderer::BatchGroup* SpriteRenderer::getNewBatch() {
    current_batch_idx_ += 1;
    T3_ASSERT(batch_groups_.size() >= current_batch_idx_);
    return &batch_groups_[current_batch_idx_];
}



void spriteTransformCore(
    Vec2& lt,
    Vec2& lb,
    Vec2& rt,
    Vec2& rb,
    const Transform2DPtr transform
) {
    //  スケーリング
    const Vec2& scale = transform->scale();
    lt *= scale;
    lb *= scale;
    rt *= scale;
    rb *= scale;


    //  回転
    float rot_z = transform->rotation().z_;

    if (!isZeroFloat(rot_z)) {
        float angle = toRadian(rot_z);
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
    const Vec2& pos = transform->position();

    lt += pos;
    lb += pos;
    rt += pos;
    rb += pos;
    
    if (transform->hasParent()) {
        spriteTransformCore(lt, lb, rt, rb, transform->parent());
    }
}


//GLsync sync;
void SpriteRenderer::margeSprites() {

    //  スプライトのソート
    std::sort(sprites_.begin(), sprites_.end(), PriorityCompare());

    Vector<VertexP2CT> vertices;
    Vector<uint32_t> indices;
    
    vertices.reserve(sprites_.size() * 4);
    indices.reserve(sprites_.size() * 8);


    Vec2 screen_size = Director::instance().virtualScreenSize();
    Vec2 half = screen_size / 2;
    half.x_ = 1.0f / half.x_;
    half.y_ = 1.0f / half.y_;


    bool add_polygon = false;
    int current_index = 0;
    //  現在のバッチグループ
    //  バッチが切れる場合はコンテナにコピーされて新たなバッチグループのインスタンスとして使う
    BatchGroup* current_batch = getNewBatch();
    
    for (int i = 0; i < sprites_.size(); ++i) {
        auto& spr = sprites_[i];
        

        if (i == 0) {
            current_batch->texture(spr->texture());
            current_batch->blendMode(spr->blendMode());
        }
    
        //
        if (isBatchGroupChange(spr, current_batch)) {
            add_polygon = false;
            current_index = 0;
            indices.pop_back();
        
            //  頂点バッファ更新
            current_batch->vertexBuffer().bind();
            current_batch->indexBuffer().bind();
            size_t vbo_size = static_cast<size_t>(vertices.size() * sizeof(VertexP2CT));
            intptr_t offset = 0;
            size_t ibo_size = static_cast<int>(indices.size() * sizeof(uint32_t));
#ifndef USE_GLMAP
            RenderSystem::setupBufferData(
                cross::RenderSystem::BufferType::TYPE_VERTEX,
                vbo_size,
                vertices.data(),
                cross::RenderSystem::BufferUsage::DYNAMIC_DRAW
            );

            //  インデックスバッファ更新
            RenderSystem::setupBufferData(
                cross::RenderSystem::BufferType::TYPE_INDEX,
                ibo_size,
                indices.data(),
                cross::RenderSystem::BufferUsage::DYNAMIC_DRAW
            );


#else
            cross::RenderSystem::fenceDrawWaiting();
            cross::RenderSystem::mapBuffer(cross::RenderSystem::BufferType::TYPE_VERTEX, offset, vbo_size, vertices.data());
            cross::RenderSystem::unmapBuffer(cross::RenderSystem::BufferType::TYPE_VERTEX);
            cross::RenderSystem::mapBuffer(cross::RenderSystem::BufferType::TYPE_INDEX, offset, ibo_size, indices.data());
            cross::RenderSystem::unmapBuffer(cross::RenderSystem::BufferType::TYPE_INDEX);
#endif
    
    
            //  ドローカウント設定
            current_batch->drawCount(static_cast<uint32_t>(indices.size()));
    
            //  バッチグループ保存
            current_batch = getNewBatch();
            
            
            //  頂点情報をクリア
            vertices.clear();
            indices.clear();
            
            //  次回のバッチグループのテクスチャを設定
            current_batch->texture(spr->texture());
            
            //  次回のバッチグループのブレンド設定を設定
            current_batch->blendMode(spr->blendMode());
        }

    
        const Vec2& pivot = spr->pivot();
        const Vec2& size = spr->size();
        
        //  初期配置
        Vec2 lt = Vec2(      0 - pivot.x_, size.y_ - pivot.y_);
        Vec2 lb = Vec2(      0 - pivot.x_, 0 - pivot.y_);
        Vec2 rt = Vec2(size.x_ - pivot.x_, size.y_ - pivot.y_);
        Vec2 rb = Vec2(size.x_ - pivot.x_, 0 - pivot.y_);
        
        spriteTransformCore(lt, lb, rt, rb, spr->transform());

        spr->rectangle().reset();
        spr->rectangle().setupFromPoint(lt);
        spr->rectangle().setupFromPoint(lb);
        spr->rectangle().setupFromPoint(rt);
        spr->rectangle().setupFromPoint(rb);
        
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
            v1.r_ = color.red();
            v1.g_ = color.green();
            v1.b_ = color.blue();
            v1.a_ = color.alpha();
            v1.tu_ = uv.u0_;
            v1.tv_ = uv.v0_;
            vertices.push_back(v1);
        }

        {
            VertexP2CT v2;
            v2.x_ = lb.x_;
            v2.y_ = lb.y_;
            v2.r_ = color.red();
            v2.g_ = color.green();
            v2.b_ = color.blue();
            v2.a_ = color.alpha();
            v2.tu_ = uv.u0_;
            v2.tv_ = uv.v1_;
            vertices.push_back(v2);
        }


        {
            VertexP2CT v3;
            v3.x_ = rt.x_;
            v3.y_ = rt.y_;
            v3.r_ = color.red();
            v3.g_ = color.green();
            v3.b_ = color.blue();
            v3.a_ = color.alpha();
            v3.tu_ = uv.u1_;
            v3.tv_ = uv.v0_;
            vertices.push_back(v3);
        }
        
 
       {
            VertexP2CT v4;
            v4.x_ = rb.x_;
            v4.y_ = rb.y_;
            v4.r_ = color.red();
            v4.g_ = color.green();
            v4.b_ = color.blue();
            v4.a_ = color.alpha();
            v4.tu_ = uv.u1_;
            v4.tv_ = uv.v1_;
            vertices.push_back(v4);
        }
        
        int first_vertex_index = current_index * 4;

        //  インデックスバッファ
        if (add_polygon) {
            //  ２スプライト目からは縮退ポリゴンを仕込む
            indices.push_back(first_vertex_index);
        }
        add_polygon = true;
        
        indices.push_back(first_vertex_index);
        indices.push_back(first_vertex_index + 1);
        indices.push_back(first_vertex_index + 2);
        indices.push_back(first_vertex_index + 3);
        indices.push_back(first_vertex_index + 3);
        
        
        current_index += 1;
    }
    
    indices.pop_back();
    

    T3_ASSERT(!vertices.empty());
    T3_ASSERT(!indices.empty());
    
            //  頂点バッファ更新
            current_batch->vertexBuffer().bind();
            current_batch->indexBuffer().bind();
            size_t vbo_size = static_cast<size_t>(vertices.size() * sizeof(VertexP2CT));
            intptr_t offset = 0;
            size_t ibo_size = static_cast<int>(indices.size() * sizeof(uint32_t));
#ifndef USE_GLMAP
            RenderSystem::setupBufferData(
                cross::RenderSystem::BufferType::TYPE_VERTEX,
                vbo_size,
                vertices.data(),
                cross::RenderSystem::BufferUsage::DYNAMIC_DRAW
            );

            //  インデックスバッファ更新
            RenderSystem::setupBufferData(
                cross::RenderSystem::BufferType::TYPE_INDEX,
                ibo_size,
                indices.data(),
                cross::RenderSystem::BufferUsage::DYNAMIC_DRAW
            );


#else
            cross::RenderSystem::fenceDrawWaiting();
            cross::RenderSystem::mapBuffer(cross::RenderSystem::BufferType::TYPE_VERTEX, offset, vbo_size, vertices.data());
            cross::RenderSystem::unmapBuffer(cross::RenderSystem::BufferType::TYPE_VERTEX);
            cross::RenderSystem::mapBuffer(cross::RenderSystem::BufferType::TYPE_INDEX, offset, ibo_size, indices.data());
            cross::RenderSystem::unmapBuffer(cross::RenderSystem::BufferType::TYPE_INDEX);
#endif
///
    
    //  ドローカウント設定
    current_batch->drawCount(static_cast<uint32_t>(indices.size()));
    

}


//  バッチが切れるか判定
bool SpriteRenderer::isBatchGroupChange(
    const SpritePtr sprite,
    const BatchGroup* current_batch
) {
    if (*sprite->texture() != *current_batch->texture()) {
        //  テクスチャが変わったらバッチが切れる
        return true;
    } else if (sprite->blendMode() != current_batch->blendMode()) {
        //  ブレンド設定が変わったらバッチが切れる
        return true;
    }


    return false;
}


void SpriteRenderer::renderBatch(BatchGroup* batch) {

    //  描画前セットアップ
    //  テクスチャ
    batch->texture()->bind();
    
    //  頂点
#ifdef USE_VAO
    batch->bindVAO();
#else
    batch->vertexBuffer().bind();
    
    shader_->setAttributePointer(
        SHADER_ATTR_POSITION,
        2,
        GL_FLOAT,
        false,
        sizeof(VertexP2CT),
        (void*)offsetof(VertexP2CT, x_)
    );

    shader_->setAttributePointer(
        SHADER_ATTR_COLOR,
        4,
        GL_UNSIGNED_BYTE,
        true,
        sizeof(VertexP2CT),
        (void*)offsetof(VertexP2CT, r_)
    );
        
    shader_->setAttributePointer(
        SHADER_ATTR_UV,
        2,
        GL_FLOAT,
        false,
        sizeof(VertexP2CT),
        (void*)offsetof(VertexP2CT, tu_)
    );

#endif

    //  インデックス
    batch->indexBuffer().bind();

    //  ブレンド設定
    cross::RenderSystem::BlendMode bmode = batch->blendMode();
    cross::RenderSystem::setBlendMode(bmode);


    // 描画
    cross::RenderSystem::drawElements(
        cross::RenderSystem::DrawMode::MODE_TRIANGLE_STRIP,
        batch->drawCount(),
        sizeof(uint32_t)
    );
#ifdef USE_VAO
    cross::RenderSystem::bindVertexArrayBuffer(0);
#endif
}


void SpriteRenderer::endRender()
{
#ifndef USE_VAO
    //  設定の後片付け
    shader_->setEnableAttributeArray(SHADER_ATTR_POSITION, false);
    shader_->setEnableAttributeArray(SHADER_ATTR_COLOR, false);
    shader_->setEnableAttributeArray(SHADER_ATTR_UV, false);
#endif

    
    //  描画設定解除
    cross::RenderSystem::setBlend(false);

    //  描画コンテナのクリア
    sprites_.clear();
    
    current_batch_idx_ = -1;

}

}   // namespace t3


