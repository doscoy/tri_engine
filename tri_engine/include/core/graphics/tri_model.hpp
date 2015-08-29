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
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


class Model;
using ModelPtr = SharedPtr<Model>;

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
    void render(const RenderInfo& info) override;

    ///
    /// メッシュを設定
    void mesh(MeshPtr& mesh) {
        mesh_ = mesh;
    }
    
    ///
    /// メッシュを取得
    MeshPtr& mesh() {
        return mesh_;
    }
    
    ///
    /// メッシュを取得
    const MeshPtr& mesh() const {
        return mesh_;
    }

    ///
    /// カリングモードを取得
    cross::RenderSystem::CullingMode cullingMode() const {
        return culling_mode_;
    }
    
    ///
    /// カリングモードを設定
    void cullingMode(
        cross::RenderSystem::CullingMode mode
    ) {
        culling_mode_ = mode;
    }

    ///
    /// 影を落とすオブジェクトか判定
    bool isShadowCaster() const {
        return shadow_cast_;
    }

    ///
    /// このモデルの影を落とすように設定する
    void enableShadowCast() {
        shadow_cast_ = true;
    }
    
    ///
    /// このモデルの影を落とさないように設定する
    void disableShadowCast() {
        shadow_cast_ = false;
    }
    
    ///
    /// 他のモデルの影をこのモデルに落とすか判定
    bool isShadowReceiver() const {
        return shadow_receive_;
    }
    
    ///
    /// 影をこのモデルに落とすよう設定
    void enalbeShadowReceive() {
        shadow_receive_ = true;
    }
    
    ///
    /// 影をこのモデルに落とさないよう設定
    void disableShadowReceive() {
        shadow_receive_ = false;
    }
    

public:
    ///
    /// モデル生成関数
    static ModelPtr create();
    static ModelPtr create(const FilePath& mesh_path);

private:
    ///
    /// メッシュ
    MeshPtr mesh_;
    
    ///
    /// デフォルトシェーダ
    Shader model_shader_;
    Shader simple_shader_;
    ///
    /// 使用しているシェーダ
    Shader* current_shader_;

    ///
    /// カリング設定
    cross::RenderSystem::CullingMode culling_mode_;

    ///
    /// 影を落とすオブジェクトフラグ
    bool shadow_cast_;
    
    ///
    /// 影を落とされるオブジェクトフラグ
    bool shadow_receive_;
};



TRI_CORE_NS_END


#endif // TRI_COLOR_HPP_INCLUDED