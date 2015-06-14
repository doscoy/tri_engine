/**
    @file tri_index_buffer.hpp
    インデックスバッファ.
*/

#ifndef TRI_INDEX_BUFFER_HPP_INCLUDED
#define TRI_INDEX_BUFFER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "cross/cross_sdk.hpp"

TRI_CORE_NS_BEGIN


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


TRI_CORE_NS_END


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
