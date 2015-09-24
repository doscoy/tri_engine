/**
    @file tri_submesh_data.hpp
    頂点情報データ.
*/

#ifndef TRI_SUBMESH_DATA_HPP_INCLUDED
#define TRI_SUBMESH_DATA_HPP_INCLUDED

//  include
#include "core/graphics/tri_vertex_types.hpp"
#include "tri_material.hpp"


TRI_CORE_NS_BEGIN


///
/// メッシュ
class SubMeshData {
public:
    using VerticesType = Vector<VertexP3NT>;
    using IndicesType = Vector<uint32_t>;


    void vertices(VerticesType& v) {
        vertices_ = v;
    }

    VerticesType& vertices() {
        return vertices_;
    }

    void indices(IndicesType& i) {
        indices_ = i;
    }

    IndicesType& indices() {
        return indices_;
    }

    void material(MaterialPtr m) {
        material_ = m;
    }

    MaterialPtr material() {
        return material_;
    }

private:
    VerticesType vertices_;
    IndicesType indices_;

    ///
    /// マテリアル
    MaterialPtr material_;


};

using SubMeshDataPtr = SharedPtr<SubMeshData>;
using SubMeshesData = Vector<SubMeshDataPtr>;
using SubMeshesDataPtr = SharedPtr<SubMeshesData>;


TRI_CORE_NS_END

#endif // TRI_MESH_HPP_INCLUDED

