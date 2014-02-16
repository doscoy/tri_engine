#ifndef TRI_INDEX_BUFFER_HPP_INCLUDED
#define TRI_INDEX_BUFFER_HPP_INCLUDED


#include "tri_buffer_object.hpp"



namespace t3 {
inline namespace gfx {

class IndexBuffer
    : public BufferObject
{
public:
    IndexBuffer( int index_count, const uint16_t* index = nullptr )
        : BufferObject( RenderSystem::BufferType::TYPE_INDEX, sizeof( uint16_t ), index_count, (void*)index )
    {
    }

public:
    void update(
        int offset,
        const GLushort* index = nullptr
    ){
        BufferObject::update( offset, index );
    }
};


}   // inline namespace gfx
}   // namespace t3


#endif // TRI_INDEX_BUFFER_HPP_INCLUDED