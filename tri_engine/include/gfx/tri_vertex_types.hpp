#ifndef TRI_VERTEX_TYPES_HPP_INCLUDED
#define TRI_VERTEX_TYPES_HPP_INCLUDED


namespace t3 {


struct VertexP2CT
{
    typedef float   position_t;
    typedef uint8_t color8_t;
    typedef float   tex_coord_t;
    
    position_t x_;
    position_t y_;
    color8_t r_;
    color8_t g_;
    color8_t b_;
    color8_t a_;
    position_t tu_;
    position_t tv_;
};

struct VertexP2T
{
    float x_;
    float y_;
    float u_;
    float v_;
};

struct VertexP3N {

    float x_;
    float y_;
    float z_;
    float nx_;
    float ny_;
    float nz_;

};



}   // namespace t3





#endif // TRI_VERTEX_TYPES_HPP_INCLUDED