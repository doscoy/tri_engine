/**
    @file tri_scene_graph.hpp
    シーングラフ.
*/

#ifndef TRI_SCENE_GRAPH_HPP_INCLUDED
#define TRI_SCENE_GRAPH_HPP_INCLUDED

#include "../math/tri_matrix_stack.hpp"
#include "tri_transform_node.hpp"
#include "tri_scene_node.hpp"
#include "tri_camera.hpp"
#include "tri_projector.hpp"

#include "util/tri_uncopyable.hpp"



namespace t3 {


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
    void renderScene();
    
    ///
    /// シーンを更新
    void updateScene(tick_t delta_time);
    
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
    void lightCamera(CameraPtr cam) {
        light_camera_ = cam;
    }
    
    ///
    /// シャドウ描画用カメラを取得
    const CameraPtr lightCamera() const {
        return light_camera_;
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
    
    /// 描画モード設定
    void renderMode(
        RenderInfo::Mode mode
    ) {
        render_mode_ = mode;
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
    /// ライトカメラ
    CameraPtr light_camera_;
    
    ///
    /// プロジェクター
    ProjectorPtr projector_;
    
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



}   // namespace t3


#endif  // TRI_SCENE_GRAPH_HPP_INCLUDED
