/**
    @file tri_sprite_renderer.hpp
    スプライトレンダラ.
*/

#ifndef TRI_SPRITE_RENDERER_HPP_INCLUDED
#define TRI_SPRITE_RENDERER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/base/tri_std.hpp"
#include "tri_shader.hpp"
#include "tri_sprite.hpp"
#include "core/graphics/tri_vertex_types.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_index_buffer.hpp"



TRI_CORE_NS_BEGIN


//  前方宣言
class IndexBuffer;

///
/// スプライトレンダラ
class SpriteRenderer
    : private Uncopyable
{
    ///
    /// バッチグループ.
    /// 効率的に描画するためのグループ
    class BatchGroup {
    public:
        ///
        /// コンストラクタ
        BatchGroup()
            : vertex_buffer_()
            , index_buffer_()
            , texture_(nullptr)
            , draw_count_(0)
            , blend_mode_(cross::RenderSystem::BlendMode::NONE)
            , vao_(0)
        {
            vao_ = cross::RenderSystem::createVertexArrayObject();
        }
        
        ///
        /// デストラクタ
        ~BatchGroup() {
            cross::RenderSystem::deleteVertexArrayBuffer(vao_);
        }
        
    public:
        ///
        /// テクスチャを取得
        const TexturePtr& texture() const {
            return texture_;
        }
        
        ///
        /// テクスチャを設定
        void texture(const TexturePtr& tex) {
            texture_ = tex;
        }
        
        ///
        /// 頂点バッファを取得
        const VertexBuffer& vertexBuffer() const {
            return vertex_buffer_;
        }
        
        ///
        /// インデックスバッファを取得
        const IndexBuffer& indexBuffer() const {
            return index_buffer_;
        }
        
        ///
        /// 描画カウント取得
        uint32_t drawCount() const {
            return draw_count_;
        }
        
        ///
        /// 描画カウントを設定
        void drawCount(uint32_t count) {
            draw_count_ = count;
        }
    
        ///
        /// ブレンドモードを設定
        void blendMode(cross::RenderSystem::BlendMode mode) {
            blend_mode_ = mode;
        }
        
        ///
        /// ブレンドモードの取得
        cross::RenderSystem::BlendMode blendMode() const {
            return blend_mode_;
        }
        
        ///
        /// VAOをバインド
        void bindVAO() {
            cross::RenderSystem::bindVertexArrayObject(vao_);
        }
    
    
    private:
        ///
        /// 頂点バッファ
        VertexBuffer vertex_buffer_;
        
        ///
        /// インデックスバッファ
        IndexBuffer index_buffer_;
        
        ///
        /// テクスチャ
        TexturePtr texture_;
        
        ///
        /// 描画数カウント
        uint32_t draw_count_;
        
        ///
        /// ブレンドモード
        cross::RenderSystem::BlendMode blend_mode_;
        
        ///
        /// VAO
        cross::RenderSystem::BufferID vao_;
    };

    ///
    /// バッチグループの集合
    using BatchGroups = Array<BatchGroup, 64>;

public:
    ///
    /// スプライトコンテナ
    using Container = Vector<SpritePtr>;

public:
    ///
    /// コンストラクタ
    SpriteRenderer();
    
    ///
    /// デストラクタ
    ~SpriteRenderer();
    
    
public:
    ///
    /// スプライトを集める
    void collectSprite(SpritePtr sprite);
    
    ///
    /// スプライトをマージする
    void margeSprites();
    
    ///
    /// 描画
    void render();
    
    ///
    /// デフォルトシェーダを使用する
    void useDefaultShader() {
        shader_ = default_shader_;
    }
    
    ///
    /// シェーダを設定
    void useCustomShader(ShaderPtr shader) {
        shader_ = shader;
    }


    ///
    /// 集めたスプライト取得
    const Container& collections() const {
        return collections_;
    }

private:
    ///
    /// 描画前処理
    void beginRender();
    
    ///
    /// 描画後処理
    void endRender();

    ///
    /// バッチグループを変更する必要があるか判定
    bool isBatchGroupChange(
        const SpritePtr sprite, ///< スプライト
        const BatchGroup* batch ///< バッチ
    );
    
    
    ///
    /// バッチ単位で描画
    void renderBatch(
        BatchGroup* batch   ///< 描画対象バッチ
    );

    ///
    /// 新しいバッチグループを取得
    SpriteRenderer::BatchGroup* getNewBatch();
    

private:
    ///
    /// 集めてきたスプライト群
    Container collections_;
    
    ///
    /// 使用するシェーダ
    ShaderPtr shader_;
    
    ///
    /// デフォルトのシェーダ
    ShaderPtr default_shader_;
    
    ///
    /// バッチグループ
    BatchGroups batch_groups_;
    
    ///
    /// カレントのバッチインデックス
    int current_batch_idx_;
};


TRI_CORE_NS_END


#endif // TRI_SPRITE_RENDERER_HPP_INCLUDED
