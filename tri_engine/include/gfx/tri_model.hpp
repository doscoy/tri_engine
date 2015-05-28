/**
    @file tri_model.hpp
    モデルエンティティ.
*/
#ifndef TRI_MODEL_HPP_INCLUDED
#define TRI_MODEL_HPP_INCLUDED

#include <memory>

//  include
#include "tri_entity.hpp"
#include "tri_mesh.hpp"
#include "tri_shader.hpp"


namespace t3 {

class Model;
using ModelPtr = ScopedPtr<Model>;

///
/// モデル
class Model
    : public Entity
{

protected:
    ///
    /// コンストラクタ
    Model();
public:
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
    
    Mesh* mesh() {
        return mesh_;
    }
    
    const Mesh* mesh() const {
        return mesh_;
    }

public:
    ///
    /// モデル生成関数
    static ModelPtr create();
    static ModelPtr create(const char* const mesh_path);

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