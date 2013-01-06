#ifndef TRI_VERTEX_TYPES_HPP_INCLUDED
#define TRI_VERTEX_TYPES_HPP_INCLUDED


namespace t3 {


struct VertexP2CT
{
    typedef float   position_t;
    typedef u_char  color_t;
    typedef float   tex_coord_t;
    
    position_t x;
    position_t y;
    color_t r;
    color_t g;
    color_t b;
    color_t a;
    position_t tu;
    position_t tv;
};



}   // namespace t3





#endif // TRI_VERTEX_TYPES_HPP_INCLUDED