

#include "core/graphics/tri_mesh.hpp"
#include "core/debug/tri_assert.hpp"
#include "core/debug/tri_trace.hpp"
#include "core/base/tri_std.hpp"
#include "core/geometry/tri_aabb.hpp"

#include "core/graphics/tri_vertex_types.hpp"

TRI_CORE_NS_BEGIN




#define BUFFER_OFFSET(bytes) ((GLubyte *)nullptr + (bytes))

//  頂点のインデックス情報を取得
int safeScanVertexIndex(
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

    *f1 -= 1;
    *f2 -= 1;
    *f3 -= 1;
    *f4 -= 1;

    return scan_count;
}

//  UV値のインデックス情報を取得
int safeScanUVIndex(
    char* buf,
    int* f1,
    int* f2,
    int* f3,
    int* f4
) {
    
    int scan_count = sscanf(buf + 2, "%*d/%d/%*d %*d/%d/%*d %*d/%d/%*d %*d/%d/%*d", f1, f2, f3, f4);
    if (scan_count != 4 && scan_count != 3) {
        return 0;
    }

    *f1 -= 1;
    *f2 -= 1;
    *f3 -= 1;
    *f4 -= 1;

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
    
    using VerticesContainer = Vector<VertexP3NT>;
    VerticesContainer vertices;
    vertices.reserve(1000);

    using IndicesContainer = Vector<uint32_t>;
    IndicesContainer indices;
    indices.reserve(1000);
    
    using UVContainer = Vector<Vec2>;
    UVContainer uvs;
    uvs.reserve(1000);
    
    IndicesContainer uv_indices;
    uv_indices.reserve(1000);
    
    

    AABB aabb;
    while (file.getline(buf, sizeof buf)) {
        if (buf[0] == 'v' && buf[1] == ' ') {
            // ------------------------------------------
            //  頂点データ取得
            Vec3 new_point;
            sscanf(buf, "%*s %f %f %f",
                &new_point.x_,
                &new_point.y_,
                &new_point.z_
            );

            VerticesContainer::value_type p3nt;
            p3nt.position_ = new_point;
            p3nt.normal_ = Vec3::zero();
            p3nt.uv_ = Vec2::zero();
            vertices.push_back(p3nt);

            aabb.margePoint(new_point);
        } else if (buf[0] == 'f' && buf[1] == ' ') {
            // -----------------------------------------
            //  面情報
            int v1, v2, v3, v4;
            
            //  頂点インデックス取得
            int scan_num = safeScanVertexIndex(buf, &v1, &v2, &v3, &v4);
            T3_ASSERT(scan_num >= 3);


            //  頂点インデックス登録
            indices.push_back(v1);
            indices.push_back(v2);
            indices.push_back(v3);
            
            if (scan_num == 4) {

                indices.push_back(v1);
                indices.push_back(v3);
                indices.push_back(v4);

            }
            
            //
            //  UVインデックス取得
            int uv1, uv2, uv3, uv4;
            int uv_scan_num = safeScanUVIndex(buf, &uv1, &uv2, &uv3, &uv4);

            if (uv_scan_num == 3) {
                uv_indices.push_back(uv1);
                uv_indices.push_back(uv2);
                uv_indices.push_back(uv3);
            } else if (uv_scan_num == 4) {
                uv_indices.push_back(uv1);
                uv_indices.push_back(uv2);
                uv_indices.push_back(uv3);
                
                uv_indices.push_back(uv1);
                uv_indices.push_back(uv3);
                uv_indices.push_back(uv4);
            }
            

            
            
            //
            //  面法線計算
            auto& face_vertex1 = vertices.at(v1);
            auto& face_vertex2 = vertices.at(v2);
            auto& face_vertex3 = vertices.at(v3);
            
            
            Vec3 v12 = face_vertex1.position_ - face_vertex2.position_;
            Vec3 v13 = face_vertex1.position_ - face_vertex3.position_;
            Vec3 normal = t3::Vec3::crossProduct(v12, v13).getNormalized();
            
            //  面法線を頂点法線に追加
            //  最終的に正規化するがここでは足すだけ
            face_vertex1.normal_ += normal;
            face_vertex2.normal_ += normal;
            face_vertex3.normal_ += normal;


            if (scan_num == 4) {
                auto& face_vertex4 = vertices.at(v4);
                face_vertex4.normal_ += normal;
            }
            
            
            
            
        } else if (buf[0] == 'm'
                && buf[1] == 't'
                && buf[2] == 'l'
                && buf[3] == 'l'
        ) {
            //----------------------------------------
            //  マテリアルファイル名
            char mtlfile[256];
            sscanf(buf, "%*s %s", mtlfile);
            T3_SYSTEM_LOG("mtlfile = %s\n",mtlfile);
            FilePath path = String(mtlfile);
            material_ = Material::create(path.fullpath().c_str());
        } else if (buf[0] == 'v' && buf[1] == 't') {
            //  UV情報
            Vec2 uv;
            sscanf(buf, "%*s %f %f", &uv.x_, &uv.y_);

            uvs.push_back(uv);
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


    //  最終的にワンインデックスのストリームを作る
    VerticesContainer final_vertices;
    IndicesContainer final_indices;

    int indices_size = indices.size();
    for (int i = 0; i < indices_size; ++i) {
        VerticesContainer::value_type vtx;
        
        T3_ASSERT(uv_indices.at(i) < uvs.size());
        vtx.uv_ = uvs.at(uv_indices.at(i));
        vtx.normal_ = vertices.at(indices.at(i)).normal_;
        vtx.position_ = vertices.at(indices.at(i)).position_;
        
        final_vertices.push_back(vtx);
        final_indices.push_back(i);
    }

    //  VAO作成
    vao_ = cross::RenderSystem::createVertexArrayObject();
    cross::RenderSystem::bindVertexArrayObject(vao_);
    
    //  最終結果を登録
    vb_.bind();
    int vertex_size = static_cast<int>(sizeof(VerticesContainer::value_type) * final_vertices.size());
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_VERTEX,
        vertex_size,
        final_vertices.data(),
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );

    ib_.bind();
    int index_data_size = static_cast<int>(sizeof(IndicesContainer::value_type) * final_indices.size());
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_INDEX,
        index_data_size,
        final_indices.data(),
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );
    
    enum {
        POSITION_SLOT,
        NORMAL_SLOT,
        UV_SLOT
    };
    
    //  頂点法線有効化
    cross::RenderSystem::setEnableVertexAttribute(NORMAL_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        NORMAL_SLOT,
        3,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VerticesContainer::value_type),
        (void*)offsetof(VerticesContainer::value_type, normal_)
    );


    //  UV有効化
    cross::RenderSystem::setEnableVertexAttribute(UV_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        UV_SLOT,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VerticesContainer::value_type),
        (void*)offsetof(VerticesContainer::value_type, uv_)
    );


    //  座標有効化
    cross::RenderSystem::setEnableVertexAttribute(POSITION_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        POSITION_SLOT,
        3,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VerticesContainer::value_type),
        0
    );


    vertex_count_ = static_cast<uint32_t>(final_vertices.size());
    index_count_ = static_cast<uint32_t>(final_indices.size());

    cross::RenderSystem::bindVertexArrayObject(0);

}


Mesh::~Mesh()
{
    cross::RenderSystem::deleteVertexArrayBuffer(vao_);
}


TRI_CORE_NS_END

