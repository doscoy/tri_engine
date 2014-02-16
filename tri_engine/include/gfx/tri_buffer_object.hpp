#ifndef TRI_BUFFER_OBJECT_HPP_INCLUDED
#define TRI_BUFFER_OBJECT_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"
#include "../kernel/tri_kernel.hpp"
#include "gfx/tri_render_system.hpp"


namespace t3 {
inline namespace gfx {
    
class BufferObject
    : private Uncopyable
{
public:
    BufferObject(
        RenderSystem::BufferType type,
        int stride,
        int element_count,
        void* data
    )   : buffer_type_(type)
        , buffer_( 0 )
        , buffer_size_( stride * element_count )
        , stride_( stride )
        , element_count_( element_count )
        , binded_(false)
    {
        RenderSystem::createBuffer(&buffer_);
        bindBuffer();
        RenderSystem::setupBufferData(
            buffer_type_,
            buffer_size_,
            data,
            RenderSystem::BufferUsage::STATIC_DRAW
        );
        unbindBuffer();
    }
    
    ~BufferObject(){
        RenderSystem::deleteBuffer(&buffer_);
    }


public:
    // *********************************************
    //  バッファのバインド
    void bindBuffer() {
        if (!binded_){
            RenderSystem::bindBuffer(buffer_type_, buffer_);
            binded_ = true;
        }
    }
    
    void unbindBuffer() {
        if (binded_){
            RenderSystem::bindBuffer(buffer_type_, 0);
        }
        binded_ = false;
    }
    
    // *********************************************
    //  バッファの更新
    void update(
        int offset,
        const void* data
    ){
        bindBuffer();
        RenderSystem::setupBufferSubData(
            buffer_type_,
            offset,
            stride_ * element_count_,
            data
        );
        unbindBuffer();
    }
    
    
    // *********************************************
    //  ストライド幅を取得
    int getStride() const {
        return stride_;
    }
    
    // *********************************************
    //  要素数を取得
    int getSize() const {
        return element_count_;
    }


private:
    uint32_t buffer_;
    RenderSystem::BufferType buffer_type_;
    int buffer_size_;
    int stride_;
    int element_count_;
    bool binded_;


};
    

}   // inline namespace gfx
}   // namespace t3


#endif // TRI_BUFFER_OBJECT_HPP_INCLUDED