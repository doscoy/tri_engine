#ifndef TRI_MESH_HPP_INCLUDED
#define TRI_MESH_HPP_INCLUDED

#include "../base/tri_types.hpp"


namespace t3 {
inline namespace gfx {


typedef float vec[3];
typedef uint32_t idx[3];

class Mesh
{
    uint32_t vertex_count_;
    uint32_t face_count_;
    vec* vert_;
    vec* normal_;
    vec* fnormal_;
    idx* face_;
    uint32_t buffers_[3];

public:
    Mesh(const char* const name);
    virtual ~Mesh();
    
public:
    void draw(void);
};

} // inline namespace gfx
} // namespace t3

#endif // TRI_MESH_HPP_INCLUDED

