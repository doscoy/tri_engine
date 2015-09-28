////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_frame_buffer.hpp
    フレームバッファ.
*/
#ifndef TRI_FRAME_BUFFER_HPP_INCLUDED
#define TRI_FRAME_BUFFER_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "cross/cross_render_system.hpp"


TRI_CORE_NS_BEGIN


///
/// 頂点バッファ
class FrameBuffer
    : Uncopyable {
public:
    ///
    /// コンストラクタ
    FrameBuffer()
        : buffer_id_(0)
        , last_buffer_id_(0)
    {
        cross::RenderSystem::createFrameBuffer(&buffer_id_);
    }
    
    ///
    /// デストラクタ
    ~FrameBuffer() {
        cross::RenderSystem::deleteFrameBuffer(&buffer_id_);
    }
    
public:
    ///
    /// バインド
    void bind() {
        last_buffer_id_ = cross::RenderSystem::getCurrentFrameBufferID();
        cross::RenderSystem::bindFrameBuffer(buffer_id_);
    }
    
    ///
    /// バインド解除
    void unbind() const {
        cross::RenderSystem::bindFrameBuffer(last_buffer_id_);
    }

private:
    ///
    /// バッファID
    cross::RenderSystem::BufferID buffer_id_;
    
    /// バインド前のバッファID
    cross::RenderSystem::BufferID last_buffer_id_;
};


TRI_CORE_NS_END


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
