#ifndef TRI_BUFFER_OBJECT_HPP_INCLUDED
#define TRI_BUFFER_OBJECT_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"
#include "../platform/platform_sdk.hpp"

namespace t3 {
inline namespace gfx {
    
class BufferObject
    : private Uncopyable
{
public:
    BufferObject(
        GLenum target,
        int stride,
        int element_count,
        void* data
    )   : target_( target )
        , buffer_( 0 )
        , buffer_size_( stride * element_count )
        , stride_( stride )
        , element_count_( element_count )
    {
        glGenBuffers( 1, &buffer_ );
        bindBuffer();
        glBufferData( target_, buffer_size_, data, GL_STATIC_DRAW_ARB );
    }
    
    ~BufferObject(){
        glDeleteBuffers( 1, &buffer_ );
    }


public:
    // *********************************************
    //  バッファのバインド
    void bindBuffer() {
        if (!binded_){
            glBindBuffer( target_, buffer_ );
            binded_ = true;
        }
    }
    
    void unbindBuffer() {
        if (binded_){
            glBindBuffer( target_, 0 );
        }
    }
    
    // *********************************************
    //  バッファの更新
    void update(
        int offset,
        const void* data
    ){
        bindBuffer();
        glBufferSubData( target_, offset, stride_ * element_count_, data );
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
    GLuint buffer_;
    GLenum target_;
    int buffer_size_;
    int stride_;
    int element_count_;
    bool binded_;


};
    

}   // inline namespace gfx
}   // namespace t3


#endif // TRI_BUFFER_OBJECT_HPP_INCLUDED