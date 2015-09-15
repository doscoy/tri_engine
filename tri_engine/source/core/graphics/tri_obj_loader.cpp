#include "core/graphics/tri_obj_loader.hpp"
#include "core/graphics/tri_mtl_loader.hpp"
#include "core/graphics/tri_vertex_types.hpp"


TRI_CORE_NS_BEGIN


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






SubMeshDataPtr ObjLoader::load(
    const char* const path
) {

    SubMeshDataPtr submesh = std::make_shared<SubMeshData>();
  
    FileStream file(path, std::ios::in | std::ios::binary);
    char buf[1024];
    
    
    T3_ASSERT_MSG(file, "%s is not found.", path);
    
    //  頂点
    auto& vertices = submesh->vertices();
    vertices.reserve(1000);

    //  頂点インデックス
    auto& indices = submesh->indices();
    indices.reserve(1000);
    
    //  UV
    auto& uvs = submesh->uvs();
    uvs.reserve(1000);
    
    //  UVインデックス
    auto& uv_indices = submesh->uvindices();
    uv_indices.reserve(1000);
    
    
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

            SubMeshData::Vertices::value_type p3nt;
            p3nt.position_ = new_point;
            p3nt.normal_ = Vec3::zero();
            p3nt.uv_ = Vec2::zero();
            vertices.push_back(p3nt);

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
            Vec3 normal = Vec3::crossProduct(v12, v13).getNormalized();
            
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
            T3_SYSTEM_LOG("mtlfile = %s¥n",mtlfile);
            FilePath path = String(mtlfile);
            //  MtlLoaderでロード
            auto material = MtlLoader::load(path.fullpath().c_str());
            submesh->material(material);

        } else if (buf[0] == 'v' && buf[1] == 't') {
            //  UV情報
            Vec2 uv;
            sscanf(buf, "%*s %f %f", &uv.x_, &uv.y_);

            uvs.push_back(uv);
        }
    }


    return submesh;
}

TRI_CORE_NS_END


