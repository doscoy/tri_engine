
#ifndef TRI_INDEX_BUFFER_HPP_INCLUDED
#define TRI_INDEX_BUFFER_HPP_INCLUDED

//  include
#include "cross_sdk.hpp"

namespace t3 {

///
/// インデックスバッファ
class IndexBuffer {
public:
    ///
    /// コンストラクタ
    IndexBuffer()
        : buffer_id_()
    {
        cross::RenderSystem::createBuffer(&buffer_id_);
    }
    
    ///
    /// デストラクタ
    ~IndexBuffer() {
        cross::RenderSystem::deleteBuffer(&buffer_id_);
    }
    
public:
    ///
    /// このインデックスバッファをレンダリングシステムに紐付け
    void bind() const {
        cross::RenderSystem::bindBuffer(cross::RenderSystem::BufferType::TYPE_INDEX, buffer_id_);
    }

private:
    cross::RenderSystem::BufferID buffer_id_;   ///< バッファID
};


}   // namespace t3


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
