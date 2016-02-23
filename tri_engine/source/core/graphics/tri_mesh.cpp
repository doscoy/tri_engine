////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/tri_mesh.hpp"
#include "core/debug/tri_assert.hpp"
#include "core/debug/tri_trace.hpp"
#include "core/geometry/tri_aabb.hpp"
#include "core/graphics/tri_obj_loader.hpp"
#include "core/graphics/tri_dae_loader.hpp"

TRI_CORE_NS_BEGIN

///
/// コンストラクタ
SubMesh::SubMesh()
    : vertex_count_(0)
    , index_count_(0)
    , vao_(0)
    , vb_()
    , ib_()
    , sphere_()
    , aabb_()
{}


///
/// サブメッシュデータからメッシュ生成
void SubMesh::setupFromSubMeshData(
    SubMeshDataPtr& submesh
) {
    auto& vertices = submesh->vertices();

    //  マテリアルをコピー
    material(submesh->material());

    //  頂点法線を正規化 & AABB作成
    for (auto& v : vertices) {
        aabb_.margePoint(v.position_);
        v.normal_.normalize();
    }

    //  ベースの姿勢行列設定
    matrix(submesh->matrix());

    //  aabbをもとに境界球作成
    Vec3 radius = aabb_.radius();
    Position3D center = aabb_.center();
    
    //  なんちゃって境界球なので
    //  大きい方の半径をそのまま使う
    float sphere_radius = radius.x_;
    if (sphere_radius < radius.y_) {
        sphere_radius = radius.y_;
    }
    if (sphere_radius < radius.z_) {
        sphere_radius = radius.z_;
    }
    
    sphere_.position(center);
    sphere_.radius(sphere_radius);



    SubMeshData::VerticesType& final_vertices = submesh->vertices();
    SubMeshData::IndicesType& final_indices = submesh->indices();

    //  VAO作成
    vao_ = cross::RenderSystem::createVertexArrayObject();
    cross::RenderSystem::bindVertexArrayObject(vao_);
    
    //  最終結果を登録
    vb_.bind();
    int vertex_size = static_cast<int>(sizeof(SubMeshData::VerticesType::value_type) * final_vertices.size());
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_VERTEX,
        vertex_size,
        final_vertices.data(),
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );

    ib_.bind();
    int index_data_size = static_cast<int>(sizeof(SubMeshData::IndicesType::value_type) * final_indices.size());
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
        sizeof(SubMeshData::VerticesType::value_type),
        (void*)offsetof(SubMeshData::VerticesType::value_type, normal_)
    );


    //  UV有効化
    cross::RenderSystem::setEnableVertexAttribute(UV_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        UV_SLOT,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(SubMeshData::VerticesType::value_type),
        (void*)offsetof(SubMeshData::VerticesType::value_type, uv_)
    );


    //  座標有効化
    cross::RenderSystem::setEnableVertexAttribute(POSITION_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        POSITION_SLOT,
        3,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(SubMeshData::VerticesType::value_type),
        0
    );


    vertex_count_ = static_cast<uint32_t>(final_vertices.size());
    index_count_ = static_cast<uint32_t>(final_indices.size());

    cross::RenderSystem::bindVertexArrayObject(0);


}


///
/// デストラクタ
SubMesh::~SubMesh() {
    cross::RenderSystem::deleteVertexArrayBuffer(vao_);
}

///
/// 生成
SubMeshPtr SubMesh::create(
    SubMeshDataPtr& res
) {
    SubMeshPtr s(T3_NEW SubMesh());
    s->setupFromSubMeshData(res);
    return s;
}



///
/// コンストラクタ
Mesh::Mesh()
    : Resource()
    , meshes_()
{
}

Mesh::~Mesh() {

}

///
/// メッシュ生成
MeshPtr Mesh::create(
    const FilePath& file_path
) {
    MeshPtr mesh(T3_NEW Mesh());
    mesh->load(file_path);
    return mesh;
}


void Mesh::load(
    const FilePath& filepath
) {
    //  リソース名設定
    resourceName(filepath.path());

    //  拡張子でローダ切り替え
    if (filepath.ext() == ".obj") {
        loadObj(filepath);
    } else if (filepath.ext() == ".dae") {
        loadDae(filepath);
    } else {
        T3_PANIC("Unknown file ext. [%s]", filepath.ext().c_str());
    }
    calcBound();
}


///
/// .objファイルのロード
void Mesh::loadObj(
    const FilePath& path
) {
    auto submeshdata = ObjLoader::load(path.fullpath().c_str());
    auto s = SubMesh::create(submeshdata);
    meshes_.push_back(s);
}

///
/// .daeファイルのロード
void Mesh::loadDae(
    const FilePath &file_path
) {
    auto submeshes = DaeLoader::load(file_path.fullpath().c_str());

    for (int i = 0; i < submeshes->size(); ++i) {
        auto& res = submeshes->at(i);
        auto s = SubMesh::create(res);
        meshes_.push_back(s);
    }
}

///
/// 境界球を計算
void Mesh::calcBound() {

    for (auto& m : meshes_) {
        aabb_.marge(m->aabb());
    }
    
    const auto& center = aabb_.center();
    const auto& radius = aabb_.radius();
    
    //  なんちゃって境界球なので
    //  大きい方の半径をそのまま使う
    float sphere_radius = radius.x_;
    if (sphere_radius < radius.y_) {
        sphere_radius = radius.y_;
    }
    if (sphere_radius < radius.z_) {
        sphere_radius = radius.z_;
    }
    
    bounding_sphere_.position(center);
    bounding_sphere_.radius(sphere_radius);
}

TRI_CORE_NS_END

