#ifndef TRI_MESH_HPP_INCLUDED
#define TRI_MESH_HPP_INCLUDED

#include "../base/tri_types.hpp"
#include "../geometry/tri_sphere.hpp"

namespace t3 {
inline namespace gfx {



class Mesh
{
    typedef float vertex_t[3];
    typedef uint32_t index_t[3];

public:
    Mesh(const char* const name);
    virtual ~Mesh();
    
public:
    void draw(void);
    
    const Sphere* getBoundingSphere() const {
        return &sphere_;
    }

private:
    uint32_t vertex_count_;
    uint32_t face_count_;
    vertex_t* vert_;
    vertex_t* normal_;
    vertex_t* fnormal_;
    index_t* face_;
    uint32_t buffers_[3];

    Sphere sphere_;
};

} // inline namespace gfx
} // namespace t3

#endif // TRI_MESH_HPP_INCLUDED

