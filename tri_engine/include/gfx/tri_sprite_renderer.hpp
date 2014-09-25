#ifndef TRI_SPRITE_RENDERER_HPP_INCLUDED
#define TRI_SPRITE_RENDERER_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "tri_render_system.hpp"
#include "base/tri_std.hpp"
#include "tri_shader.hpp"
#include "tri_sprite.hpp"
#include "gfx/tri_vertex_types.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_index_buffer.hpp"

namespace t3 {
inline namespace gfx {

class IndexBuffer;
class SpriteRenderer
    : private Uncopyable
{
    class BatchGroup {
    public:
        BatchGroup()
            : vertex_buffer_()
            , index_buffer_()
            , texture_(nullptr)
            , draw_count_(0)
            , blend_mode_(RenderSystem::BlendMode::NONE)
        {
        }
        
        ~BatchGroup() {
        }
        
    public:
        const TexturePtr& texture() const {
            return texture_;
        }
        
        void texture(const TexturePtr& tex) {
            texture_ = tex;
        }
        
        const VertexBuffer& vertexBuffer() const {
            return vertex_buffer_;
        }
        
        const IndexBuffer& indexBuffer() const {
            return index_buffer_;
        }
        
        uint32_t drawCount() const {
            return draw_count_;
        }
        
        void drawCount(uint32_t count) {
            draw_count_ = count;
        }
    
        void blendMode(RenderSystem::BlendMode mode) {
            blend_mode_ = mode;
        }
        
        RenderSystem::BlendMode blendMode() const {
            return blend_mode_;
        }
    
    
    private:
        VertexBuffer vertex_buffer_;
        IndexBuffer index_buffer_;
        TexturePtr texture_;
        uint32_t draw_count_;
        RenderSystem::BlendMode blend_mode_;
    };
    using BatchGroups = Vector<SharedPtr<BatchGroup>>;
    using Container = Vector<SpritePtr>;

public:
    SpriteRenderer();
    ~SpriteRenderer();
    
    
public:
    void collectSprite(SpritePtr sprite);
    void render();
    
    void useDefaultShader() {
        shader_ = default_shader_;
    }
    
    void useCustomShader(ShaderPtr shader) {
        shader_ = shader;
    }

private:
    void beginRender();
    void endRender();

    bool isBatchGroupChange(
        const SpritePtr sprite,
        const SharedPtr<BatchGroup>& batch
    );
    void margeSprites();
    void renderBatch(SharedPtr<BatchGroup>& batch);

private:
    Container sprites_;
    ShaderPtr shader_;
    ShaderPtr default_shader_;
    BatchGroups batch_groups_;

};



}   // inline namespace gfx
}   // namespace t3




#endif // TRI_SPRITE_RENDERER_HPP_INCLUDED