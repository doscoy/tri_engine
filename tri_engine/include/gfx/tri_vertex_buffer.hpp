
#ifndef TRI_VERTEX_BUFFER_HPP_INCLUDED
#define TRI_VERTEX_BUFFER_HPP_INCLUDED



#include "tri_buffer_object.hpp"
#include "tri_vertex_types.hpp"



namespace t3 {
inline namespace gfx {
    

template <typename Vertex>
class VertexBuffer
    : public BufferObject
{   
public:
    VertexBuffer(
        int vertex_count,
        Vertex* vertex = nullptr
    )   : BufferObject(GL_ARRAY_BUFFER, sizeof(Vertex), vertex_count, vertex )
    {
    }
    
 
public:
    void update(
        int offset,
        const Vertex* vertex
    ){
        BufferObject::update( 
            offset, 
            vertex 
        );
    }
    
};

}   // inline namespace gfx
}   // namespace t3


#endif // TRI_VERTEX_BUFFER_HPP_INCLUDED
