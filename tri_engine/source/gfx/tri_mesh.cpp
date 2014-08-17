

#include "gfx/tri_mesh.hpp"
#include "dbg/tri_assert.hpp"
#include <fstream>
#include "platform/platform_sdk.hpp"
#include "geometry/tri_aabb.hpp"
#include "gfx/tri_render_system.hpp"
#include "gfx/tri_vertex_types.hpp"


namespace t3 {
inline namespace gfx {

#define BUFFER_OFFSET(bytes) ((GLubyte *)nullptr + (bytes))


int safeScan(
    char* buf,
    int* f1,
    int* f2,
    int* f3,
    int* f4
) {
    
    int scan_count = sscanf(buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", f1, f2, f3, f4);
    if (scan_count != 4 && scan_count != 3) {
        scan_count = sscanf(buf + 2, "%d %d %d %d", f1, f2, f3, f4);
        if (scan_count != 4 && scan_count != 3) {
            return 0;
        }
    }

    return scan_count;
}


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
            p3n.position_ = new_point;
            p3n.normal_ = Vec3::zero();
            vertices.push_back(p3n);

            aabb.addPoint(new_point);
        } else if (buf[0] == 'f' && buf[1] == ' ') {
            //  面情報
            int f1, f2, f3, f4;
            
            //  いろんなフォーマットがある
            int scan_num = safeScan(buf, &f1, &f2, &f3, &f4);
            T3_ASSERT(scan_num >= 3);
            f1 -= 1;
            f2 -= 1;
            f3 -= 1;
            f4 -= 1;


            //  頂点インデックス登録
            indices.push_back(f1);
            indices.push_back(f2);
            indices.push_back(f3);
            
            if (scan_num == 4) {

                indices.push_back(f1);
                indices.push_back(f3);
                indices.push_back(f4);

            }
            
            
            //  e面法線計算
            auto& face_vertex1 = vertices.at(f1);
            auto& face_vertex2 = vertices.at(f2);
            auto& face_vertex3 = vertices.at(f3);
            
            
            Vec3 v12 = face_vertex1.position_ - face_vertex2.position_;
            Vec3 v13 = face_vertex1.position_ - face_vertex3.position_;
            Vec3 normal = t3::Vec3::crossProduct(v12, v13).getNormalized();
            
            //  面法線を頂点法線に追加
            //  最終的に正規化するがここでは足すだけ
            face_vertex1.normal_ += normal;
            face_vertex2.normal_ += normal;
            face_vertex3.normal_ += normal;

            if (scan_num == 4) {
                auto& face_vertex4 = vertices.at(f4);
                face_vertex4.normal_ += normal;
            }
        }
    }
    
    
    //  頂点法線を正規化
    for (auto& v : vertices) {
    
        v.normal_.normalize();
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

