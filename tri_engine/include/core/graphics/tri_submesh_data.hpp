////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_submesh_data.hpp
    頂点情報データ.
*/

#ifndef TRI_SUBMESH_DATA_HPP_INCLUDED
#define TRI_SUBMESH_DATA_HPP_INCLUDED

//  include
#include "core/graphics/tri_vertex_types.hpp"
#include "tri_material.hpp"
#include "core/math/tri_matrix.hpp"

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
    
    void matrix(Mtx44& mtx) {
        matrix_ = mtx;
    }
    
    const Mtx44& matrix() const {
        return matrix_;
    }

private:
    ///
    ///  頂点
    VerticesType vertices_;

    ///
    ///  インデックス
    IndicesType indices_;

    ///
    /// 基本姿勢
    Mtx44 matrix_;

    ///
    /// マテリアル
    MaterialPtr material_;


};

using SubMeshDataPtr = SharedPtr<SubMeshData>;
using SubMeshesData = Vector<SubMeshDataPtr>;
using SubMeshesDataPtr = SharedPtr<SubMeshesData>;


TRI_CORE_NS_END

#endif // TRI_MESH_HPP_INCLUDED

