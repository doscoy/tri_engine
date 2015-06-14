/**
    @file tri_scene_graph.hpp
    シーングラフ.
*/

#ifndef TRI_SCENE_GRAPH_HPP_INCLUDED
#define TRI_SCENE_GRAPH_HPP_INCLUDED

#include "core/core_config.hpp"
#include "../math/tri_matrix_stack.hpp"
#include "tri_transform_node.hpp"
#include "tri_scene_node.hpp"
#include "tri_camera.hpp"
#include "tri_projector.hpp"

#include "core/utility/tri_uncopyable.hpp"



TRI_CORE_NS_BEGIN



///
/// ノードコンテナ
using SceneNodeMap = std::map<NodeID, SceneNodePtr>;

//  前方参照
class TestObjectNode;
class CameraNode;
class SkyNode;

///
/// シーングラフ
class SceneGraph
    : Uncopyable
{
public:

    ///
    /// コンストラクタ
    SceneGraph();
    
    ///
    /// デストラクタ
    virtual ~SceneGraph();
    
public:
    ///
    /// ビューを設定
    void setupView();
    
    ///
    /// シーンを描画
    void renderScene(RenderInfo::Mode mode);
    
    ///
    /// ノードを検索
    SceneNodePtr findNode(
        NodeID id   ///< ノードID
    );
    
    
    ///
    /// カメラを設定
    void camera(
        CameraPtr cam   ///< カメラ
    ) {
        camera_ = cam;
    }
    
    ///
    /// カメラを取得
    const CameraPtr camera() const {
        return camera_;
    }
    
    ///
    /// シャドウ描画用カメラを設定
    void shadowCamera(CameraPtr cam) {
        shadow_camera_ = cam;
    }
    
    ///
    /// シャドウ描画用カメラを取得
    const CameraPtr shadowCamera() const {
        return shadow_camera_;
    }
    
    
    ///
    /// ルートノード取得
    const TransformNodePtr getRootNode() const {
        return root_;
    }
    
    ///
    /// 行列を積む
    void pushAndSetMatrix(
        const Mtx44& to_world   ///< 行列
    );
    
    ///
    /// 行列を外す
    void popMatrix();
    
    ///
    /// 最上位行列を取得
    const Mtx44* topMatrix();
    
    ///
    /// ノード生成
    TransformNodePtr createNode();
    
    ///
    /// 影用テクスチャ
    TexturePtr shadowTexture() {
        return shadow_texture_;
    }
    
    ///
    /// 影用テクスチャ
    void shadowTexture(TexturePtr tex) {
        shadow_texture_ = tex;
    }

    ///
    /// 描画モード取得
    RenderInfo::Mode renderMode() const {
        return render_mode_;
    }
    

    ///
    /// プロジェクターを取得
    ProjectorPtr& projector() {
        return projector_;
    }

    ///
    /// プロジェクターを設定
    void projector(
        ProjectorPtr& projector
    ) {
        projector_ = projector;
    }
    
    ///
    /// 影用プロジェクターを取得
    ProjectorPtr& shadowProjector() {
        return shadow_projector_;
    }

    ///
    /// 影用プロジェクターを設定
    void shadowProjector(
        ProjectorPtr& projector
    ) {
        shadow_projector_ = projector;
    }


private:

    ///
    /// 子を追加
    bool addChild(
        NodeID id,              ///< ノードID
        TransformNodePtr kid    ///< ノード
    ) {
        node_map_[id] = kid;
        return root_->addChild(kid);
    }

    ///
    /// 子を削除
    bool removeChild(
        NodeID id           ///< ノードID
    ) {
        node_map_.erase(id);
        return root_->removeChild(id);
    }
    



protected:
    ///
    /// ルートノード
    TransformNodePtr root_;
    
    ///
    /// カメラ
    CameraPtr camera_;
    
    ///
    /// 影用カメラ
    CameraPtr shadow_camera_;
    
    ///
    /// プロジェクター
    ProjectorPtr projector_;
    
    ///
    /// 影用プロジェクター
    ProjectorPtr shadow_projector_;
    
    ///
    /// 行列スタック
    MatrixStack matrix_stack_;
    
    ///
    /// 子ノード
    SceneNodeMap node_map_;
    
    ///
    /// シャドウ用テクスチャ
    TexturePtr shadow_texture_;

    ///
    /// 描画モード
    RenderInfo::Mode render_mode_;
};



TRI_CORE_NS_END


#endif  // TRI_SCENE_GRAPH_HPP_INCLUDED
