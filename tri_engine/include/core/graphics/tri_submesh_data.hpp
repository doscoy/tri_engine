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
    using Vertices = Vector<VertexP3NT>;
    using Indices = Vector<uint32_t>;
    using Uvs = Vector<Vec2>;


    void vertices(Vertices& v) {
        vertices_ = v;
    }

    Vertices& vertices() {
        return vertices_;
    }

    Indices& indices() {
        return indices_;
    }

    Uvs& uvs() {
        return uvs_;
    }

    Indices& uvindices() {
        return uv_indices_;
    }

    void material(MaterialPtr m) {
        material_ = m;
    }

    MaterialPtr material() {
        return material_;
    }

private:
    Vertices vertices_;
    Indices indices_;
    Uvs uvs_;
    Indices uv_indices_;

    ///
    /// マテリアル
    MaterialPtr material_;


};

using SubMeshDataPtr = SharedPtr<SubMeshData>;


TRI_CORE_NS_END

#endif // TRI_MESH_HPP_INCLUDED

