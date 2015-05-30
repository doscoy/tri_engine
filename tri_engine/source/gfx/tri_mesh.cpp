

#include "gfx/tri_mesh.hpp"
#include "dbg/tri_assert.hpp"

#include "base/tri_std.hpp"
#include "geometry/tri_aabb.hpp"

#include "gfx/tri_vertex_types.hpp"


namespace t3 {



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
    , vb_()
    , ib_()
    , sphere_()
{
    FileStream file(name, std::ios::in | std::ios::binary);
    char buf[1024];
    
    
    T3_ASSERT_MSG(file, "%s is not found.", name);
    

    Vector<VertexP3NT> vertices;
    Vector<uint32_t> indices;
    
    vertices.reserve(1000);
    indices.reserve(1000);
    

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
            
            VertexP3NT p3nt;
            p3nt.position_ = new_point;
            p3nt.normal_ = Vec3::zero();
            p3nt.uv_ = Vec2::zero();
            vertices.push_back(p3nt);

            aabb.margePoint(new_point);
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
            
            
            //  面法線計算
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
    Vec3 radius = aabb.radius();
    Vec3 center = aabb.center();
    
    float sphere_radius = radius.x_;
    if (sphere_radius < radius.y_) {
        sphere_radius = radius.y_;
    }
    if (sphere_radius < radius.z_) {
        sphere_radius = radius.z_;
    }
    
    sphere_.position(center);
    sphere_.radius(sphere_radius);


    vb_.bind();
    int vertex_size = static_cast<int>(sizeof(VertexP3N) * vertices.size());
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_VERTEX,
        vertex_size,
        vertices.data(),
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );

    ib_.bind();
    int index_data_size = static_cast<int>(sizeof(uint32_t) * indices.size());
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_INDEX,
        index_data_size,
        indices.data(),
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );
    

    vertex_count_ = static_cast<uint32_t>(vertices.size());
    index_count_ = static_cast<uint32_t>(indices.size());
}


Mesh::~Mesh()
{
}


} // namespace t3

