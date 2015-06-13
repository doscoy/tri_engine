/**
    @file tri_vertex_buffer.hpp
    頂点バッファ.
*/
#ifndef TRI_VERTEX_BUFFER_HPP_INCLUDED
#define TRI_VERTEX_BUFFER_HPP_INCLUDED


//  include
#include "core_config.hpp"
#include "utility/tri_uncopyable.hpp"



TRI_CORE_NS_BEGIN


///
/// 頂点バッファ
class VertexBuffer
    : Uncopyable {
public:
    ///
    /// コンストラクタ
    VertexBuffer()
        : buffer_id_()
    {
        cross::RenderSystem::createBuffer(&buffer_id_);
    }
    
    ///
    /// デストラクタ
    ~VertexBuffer() {
        cross::RenderSystem::deleteBuffer(&buffer_id_);
    }
    
public:
    ///
    /// バインド
    void bind() const {
        cross::RenderSystem::bindBuffer(cross::RenderSystem::BufferType::TYPE_VERTEX, buffer_id_);
    }
    
    ///
    /// バインド解除
    void unbind() const {
        cross::RenderSystem::bindBuffer(cross::RenderSystem::BufferType::TYPE_VERTEX, 0);
    }

private:
    ///
    /// バッファID
    cross::RenderSystem::BufferID buffer_id_;
};


TRI_CORE_NS_END


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
