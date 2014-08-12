#ifndef TRI_MESH_HPP_INCLUDED
#define TRI_MESH_HPP_INCLUDED

#include "base/tri_types.hpp"
#include "geometry/tri_sphere.hpp"
#include "tri_entity.hpp"
#include "tri_renderable.hpp"
#include "tri_render_system.hpp"
#include "util/tri_uncopyable.hpp"


namespace t3 {
inline namespace gfx {



class Mesh
    : Uncopyable
{
public:
    Mesh(const char* const name);
    virtual ~Mesh();
    
public:
    uint32_t vertexCount() const {
        return vertex_count_;
    }
    
    uint32_t indexCount() {
        return index_count_;
    }
    
    RenderSystem::BufferID vertexBuffer() const {
        return vb_;
    }
    
    RenderSystem::BufferID indexBuffer() const {
        return ib_;
    }
    
    const Sphere* getBoundingSphere() const {
        return &sphere_;
    }

private:
    uint32_t vertex_count_;
    uint32_t index_count_;
    RenderSystem::BufferID vb_;
    RenderSystem::BufferID ib_;
    Sphere sphere_;
};

} // inline namespace gfx
} // namespace t3

#endif // TRI_MESH_HPP_INCLUDED

