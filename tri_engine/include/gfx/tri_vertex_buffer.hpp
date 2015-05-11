/**
    @file tri_vertex_buffer.hpp
    頂点バッファ.
*/
#ifndef TRI_VERTEX_BUFFER_HPP_INCLUDED
#define TRI_VERTEX_BUFFER_HPP_INCLUDED


//  include
#include "util/tri_uncopyable.hpp"



namespace t3 {

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

private:
    ///
    /// バッファID
    cross::RenderSystem::BufferID buffer_id_;
};


}   // namespace t3


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
