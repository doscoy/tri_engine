

#include "tri_mesh.hpp"
#include "dbg/tri_assert.hpp"
#include <fstream>
#include "platform/platform_sdk.hpp"
#include "geometry/tri_aabb.hpp"
#include "gfx/tri_render_system.hpp"
#include "gfx/tri_vertex_types.hpp"


namespace t3 {
inline namespace gfx {

#define BUFFER_OFFSET(bytes) ((GLubyte *)nullptr + (bytes))



Mesh::Mesh(
    const char* const name
)   : vertex_count_(0)
    , index_count_(0)
    , vb_(0)
    , ib_(0)
    , sphere_()
{
    std::ifstream file(name, std::ios::in | std::ios::binary);
    char buf[1024];
    
    
    T3_ASSERT_MSG(file, "%s is not found.", name);
    

    std::vector<VertexP3N> vertices;
    std::vector<uint32_t> indices;
    

    AABB aabb;
    while (file.getline(buf, sizeof buf)) {
        //  頂点データ取得
        if (buf[0] == 'v' && buf[1] == ' ') {
        
            
            Vec3 new_point;
            sscanf(buf, "%*s %f %f %f",
                &new_point.x_,
                &new_point.y_,
                &new_point.z_
            );
            
            VertexP3N p3n;
            p3n.x_ = new_point.x_;
            p3n.y_ = new_point.y_;
            p3n.z_ = new_point.z_;
            p3n.nx_ = 1.0f;
            p3n.ny_ = 0.0f;
            p3n.nz_ = 0.0f;
            
            vertices.push_back(p3n);

            aabb.addPoint(new_point);
        } else if (buf[0] == 'f' && buf[1] == ' ') {
            //  面情報
            int f1, f2, f3, f4;
            
            //  いろんなフォーマットがある
            if (sscanf(buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &f1, &f2, &f3, &f4) != 4) {

            }
            f1 -= 1;
            f2 -= 1;
            f3 -= 1;
            f4 -= 1;
            
            indices.push_back(f1);
            indices.push_back(f2);
            indices.push_back(f3);

            indices.push_back(f1);
            indices.push_back(f3);
            indices.push_back(f4);
        }
    }
    
    //  aabbをもとに境界球作成
    Vec3 radius;
    Vec3 center;
    aabb.center(&center);
    aabb.getRadius(&radius);
    
    float sphere_radius = radius.x_;
    if (sphere_radius < radius.y_) {
        sphere_radius = radius.y_;
    }
    if (sphere_radius < radius.z_) {
        sphere_radius = radius.z_;
    }
    
    sphere_.position(center);
    sphere_.radius(sphere_radius);


    RenderSystem::createBuffer(&vb_);
    RenderSystem::bindBuffer(RenderSystem::BufferType::TYPE_VERTEX, vb_);
    RenderSystem::setupBufferData(
        RenderSystem::BufferType::TYPE_VERTEX,
        sizeof(VertexP3N) * vertices.size(),
        vertices.data(),
        RenderSystem::BufferUsage::STATIC_DRAW
    );
    
    ib_ = RenderSystem::createIndexBuffer(indices);
    

    vertex_count_ = vertices.size();
    index_count_ = indices.size();
}


Mesh::~Mesh()
{
    
    
    RenderSystem::deleteBuffer(&vb_);
    RenderSystem::deleteBuffer(&ib_);

}



} // inline namespace gfx
} // namespace t3

