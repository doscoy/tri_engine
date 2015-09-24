/**
    @file tri_mesh.hpp
    メッシュ.
*/

#ifndef TRI_MESH_HPP_INCLUDED
#define TRI_MESH_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/base/tri_types.hpp"
#include "core/geometry/tri_sphere.hpp"
#include "core/geometry/tri_aabb.hpp"
#include "tri_entity.hpp"
#include "tri_renderable.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "tri_index_buffer.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_material.hpp"
#include "tri_submesh_data.hpp"


TRI_CORE_NS_BEGIN


class SubMesh;
using SubMeshPtr = SharedPtr<SubMesh>;


///
/// メッシュ
class SubMesh {
private:
    ///
    /// コンストラクタ
    SubMesh();

public:
    ///
    /// デストラクタ
    virtual ~SubMesh();
    
public:

    ///
    /// バインド
    void bind() {
        cross::RenderSystem::bindVertexArrayObject(vao_);
    }
    
    ///
    /// バインド解除
    void unbind() {
        cross::RenderSystem::bindVertexArrayObject(0);
    }

    ///
    /// 頂点数を取得
    uint32_t vertexCount() const {
        return vertex_count_;
    }
    
    ///
    /// インデックスカウントを取得
    uint32_t indexCount() {
        return index_count_;
    }
    
    ///
    /// 頂点バッファを取得
    const VertexBuffer& vertexBuffer() const {
        return vb_;
    }
    
    ///
    /// インデックスバッファを取得
    const IndexBuffer& indexBuffer() const {
        return ib_;
    }
    
    ///
    /// 境界球を取得
    const Sphere& boundingSphere() const {
        return sphere_;
    }

    const AABB& aabb() const {
        return aabb_;
    }
    
    ///
    /// マテリアルを取得
    const MaterialPtr material() const {
        return material_;
    }

    ///
    /// マテリアルを設定
    void material(const MaterialPtr& m) {
        material_ = m;
    }

    static SubMeshPtr create(SubMeshDataPtr& data);

private:
    void setupFromSubMeshData(
        SubMeshDataPtr& vertices
    );


private:
    ///
    /// 頂点数
    uint32_t vertex_count_;
    
    ///
    /// インデックス数
    uint32_t index_count_;
    
    
    ///
    /// VAO
    cross::RenderSystem::BufferID vao_;
    
    ///
    /// 頂点バッファ
    VertexBuffer vb_;
    
    ///
    /// インデックスバッファ
    IndexBuffer ib_;
    
    ///
    /// 境界球
    Sphere sphere_;
    
    ///
    /// AABB
    AABB aabb_;
    
    ///
    /// マテリアル
    MaterialPtr material_;



};




////////
class Mesh;
using MeshPtr = SharedPtr<Mesh>;

class Mesh
    : Resource
{
public:
    Mesh();
    ~Mesh();


    static MeshPtr create(
        const FilePath& path
    );
    
    
    
    void load(
        const FilePath& filepath
    );

    void loadObj(
        const FilePath& filepath
    );

    void loadDae(
        const FilePath& filepath
    );

    
    auto& meshes() {
        return meshes_;
    }
    
    const auto& meshes() const {
        return meshes_;
    }
    
    auto& boundingSphere() {
        return bounding_sphere_;
    }
    
    const auto& boundingSphere() const {
        return bounding_sphere_;
    }
    
private:
    Sphere bounding_sphere_;
    Vector<SubMeshPtr> meshes_;
};


TRI_CORE_NS_END

#endif // TRI_MESH_HPP_INCLUDED

