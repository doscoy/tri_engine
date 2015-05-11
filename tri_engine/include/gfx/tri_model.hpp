/**
    @file tri_model.hpp
    モデルエンティティ.
*/
#ifndef TRI_MODEL_HPP_INCLUDED
#define TRI_MODEL_HPP_INCLUDED


//  include
#include "tri_entity.hpp"
#include "tri_mesh.hpp"
#include "tri_shader.hpp"


namespace t3 {


///
/// モデル
class Model
    : public Entity
{
public:
    ///
    /// コンストラクタ
    Model();
    
    ///
    /// デストラクタ
    ~Model();
    
public:
    ///
    /// 描画可能判定
    bool isRenderable() const override {
        return mesh_ != 0;
    }
    
    ///
    /// 描画
    void render(const Mtx44& transform) override;

    ///
    /// メッシュを設定
    void mesh(Mesh* mesh) {
        mesh_ = mesh;
    }


private:
    ///
    /// メッシュ
    Mesh* mesh_;
    
    ///
    /// デフォルトシェーダ
    Shader default_shader_;
    
    ///
    /// 使用しているシェーダ
    Shader* current_shader_;
};



}   // namespace t3


#endif // TRI_COLOR_HPP_INCLUDED