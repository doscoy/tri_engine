/**
    @file tri_mesh.hpp
    メッシュ.
*/

#ifndef TRI_MESH_HPP_INCLUDED
#define TRI_MESH_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "base/tri_types.hpp"
#include "geometry/tri_sphere.hpp"
#include "tri_entity.hpp"
#include "tri_renderable.hpp"
#include "utility/tri_uncopyable.hpp"
#include "tri_index_buffer.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_material.hpp"



TRI_CORE_NS_BEGIN


///
/// メッシュ
class Mesh
    : Uncopyable
{
public:
    ///
    /// コンストラクタ
    Mesh(const char* const name);
    
    ///
    /// デストラクタ
    virtual ~Mesh();
    
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

    ///
    /// マテリアルを取得
    const MaterialPtr material() const {
        return material_;
    }

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
    /// マテリアル
    MaterialPtr material_;
};


TRI_CORE_NS_END

#endif // TRI_MESH_HPP_INCLUDED

