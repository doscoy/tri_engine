#ifndef TRI_VERTEX_TYPES_HPP_INCLUDED
#define TRI_VERTEX_TYPES_HPP_INCLUDED


namespace t3 {


struct VertexP2CT
{
    typedef float   position_t;
    typedef uint8_t color8_t;
    typedef float   tex_coord_t;
    
    position_t x;
    position_t y;
    color8_t r;
    color8_t g;
    color8_t b;
    color8_t a;
    position_t tu;
    position_t tv;
};

struct VertexP2T
{
    float x;
    float y;
    float u;
    float v;
};

}   // namespace t3





#endif // TRI_VERTEX_TYPES_HPP_INCLUDED