////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_transform_node.hpp
    トランスフォームノード.
*/

#ifndef TRI_TRANSFORM_NODE_HPP_INCLUDED
#define TRI_TRANSFORM_NODE_HPP_INCLUDED

//  include
#include "tri_scene_node.hpp"
#include "core/core_config.hpp"
#include "tri_entity.hpp"

TRI_CORE_NS_BEGIN


//  前方宣言
class TransformNode;

///
/// トランスフォームノードのポインタ
using TransformNodePtr = SharedPtr<TransformNode>;

///
/// トランスフォームノード
class TransformNode
    : public ISceneNode
{
public:
    ///
    /// デストラクタ
    virtual~ TransformNode();
    
protected:
    ///
    /// コンストラクタ
    TransformNode(
        NodeID id,
        String name
    );
    
public:
    ///
    /// トランスフォームノードを生成
    static TransformNodePtr create(
        String name
    );
    
public:
    ///
    /// ノードIDを取得
    NodeID getNodeID() const override {
        return node_id_;
    }

    ///
    /// ノードにエンティティをアタッチ
    void entity(
        EntityPtr entity
    ) {
        entity_ = entity;
    }

    ///
    /// ノードにアタッチしているエンティティを取得
    EntityPtr entity() {
        return entity_;
    }
    
    ///
    /// ノードにアタッチしているエンティティを取得
    const EntityPtr entity() const {
        return entity_;
    }

    ///
    /// オブジェクトをデタッチ
    void detachEntity() {
        entity_.reset();
    }
    
    ///
    /// オブジェクトを持っているか判定
    bool hasEntity() const {
        return entity_ != nullptr;
    }
    
    ///
    /// 描画
    void render(
        SceneGraph* scene_graph
    ) override;
    
    ///
    /// 描画前処理
    bool preRender(
        t3::SceneGraph* scene_graph
    ) override;
    
    ///
    /// 描画後処理
    void postRender(
        t3::SceneGraph* scene_graph
    ) override;
    
    ///
    /// 親を取得
    ISceneNode* getParent() override {
        return parent_;
    }
    
    ///
    /// 親を取得
    const ISceneNode* getParent() const override {
        return parent_;
    }
    
    
    ///
    /// 親を設定
    void setParent(
        ISceneNode* p
    ) override {
        parent_ = p;
    }
    
    
    ///
    /// 更新
    void onUpdate(
        SceneGraph* scene_graph,
        const FrameInfo& frame_info
    ) override;
    
    
    ///
    /// 表示判定
    bool isVisible(
        SceneGraph* scene_graph ///< シーングラフ
    ) const override;
    
    
    ///
    /// 子ノードを描画
    void renderChildren(
        SceneGraph* scene_graph
    ) override;
    
    ///
    /// 子ノードを追加
    bool addChild(
        SceneNodePtr kid
    ) override;
    
    ///
    /// 子ノードを削除
    bool removeChild(
        NodeID id
    ) override;
    
    ///
    /// 親からデタッチ
    void detachParent(
        SceneNodePtr kid
    );

    ///
    /// ノード名を取得
    String getNodeName() const {
        return String();
    }

    ///
    /// ノードを生成
    TransformNodePtr createNode(
        String name
    );

    ///
    /// ノードを生成
    TransformNodePtr createNode();

public:
    ///
    /// 座標を設定
    void position(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        position_.x_ = x;
        position_.y_ = y;
        position_.z_ = z;
    }
    
    ///
    /// 座標を設定
    void position(
        const Position3D& v
    ) {
        calc_request_ = true;
        position_ = v;
    }
    
    ///
    /// 座標を取得
    const Position3D& position() const {
        return position_;
    }
    
    ///
    /// 座標を加算
    void addPosition(
        const Position3D& v
    ) {
        calc_request_ = true;
        position_ += v;
    }
    
    ///
    /// x座標を加算
    void addPositionX(
        const float v
    ) {
        calc_request_ = true;
        position_.x_ += v;
    }
    
    ///
    /// y座標を加算
    void addPositionY(
        const float v
    ) {
        calc_request_ = true;
        position_.y_ += v;
    }
    
    ///
    /// x座標を加算
    void addPositionZ(
        const float v
    ) {
        calc_request_ = true;
        position_.z_ += v;
    }
    
    ///
    /// 回転情報を設定
    void rotation(
        Degree x,
        Degree y,
        Degree z
    ) {
        calc_request_ = true;
        rotation_.x_ = x;
        rotation_.y_ = y;
        rotation_.z_ = z;
    }
    
    
    ///
    /// x軸回転を設定
    void rotationX(
        const Degree r
    ) {
        calc_request_ = true;
        rotation_.x_ = r;
    }
    
    ///
    /// y軸回転を設定
    void rotationY(
        const Degree r
    ) {
        calc_request_ = true;
        rotation_.y_ = r;
    }
    
    ///
    /// z軸回転を設定
    void rotationZ(
        const Degree r
    ) {
        calc_request_ = true;
        rotation_.z_ = r;
    }
    
    ///
    /// 回転情報を設定
    void rotation(
        const Rotation& v
    ) {
        calc_request_ = true;
        rotation_ = v;
    }
    
    ///
    /// 回転情報を取得
    const Rotation& rotation() const {
        return rotation_;
    }
    
    ///
    /// x軸回転を加算
    void addRotationX(
        const Degree r
    ) {
        calc_request_ = true;
        rotation_.x_ += r;
    }
    
    ///
    /// y軸回転を加算
    void addRotationY(
        const Degree r
    ) {
        calc_request_ = true;
        rotation_.y_ += r;
    }
    
    ///
    /// ｚ軸回転を加算
    void addRotationZ(
        const Degree r
    ) {
        calc_request_ = true;
        rotation_.z_ += r;
    }

    ///
    /// スケール
    void scale(float s) {
        scale(s, s, s);
    }

    
    ///
    /// スケール
    void scale(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        scale_.x_ = x;
        scale_.y_ = y;
        scale_.z_ = z;
    }
    
    ///
    /// スケール設定
    void scale(
        const Scale3D& v
    ) {
        calc_request_ = true;
        scale_ = v;
    }
    
    ///
    /// スケール取得
    const Scale3D& scale() const {
        return scale_;
    }
    
    ///
    /// 表示設定
    void setVisible(
        const bool visible
    ) {
        visible_ = visible;
    }

    ///
    /// 表示判定
    bool isVisible() const {
        return visible_;
    }

    ///
    /// 行列を取得
    const Mtx44* getTransformMatrix();

private:
    ///
    /// トランスフォーム行列を作成
    void makeTransformMatrix();


private:
    ///
    /// 座標
    Position3D position_;
    
    ///
    /// 回転情報
    Rotation rotation_;
    
    ///
    /// スケール
    Scale3D scale_;
    
    ///
    /// 描画フラグ
    bool visible_;
    
    ///
    /// 姿勢行列
    Mtx44 transform_;
    
    ///
    /// 行列計算リクエスト
    bool calc_request_;
    
    ///
    /// ノードにひもづけるオブジェクト
    EntityPtr entity_;
    
    ///
    /// 子ノード
    SceneNodeList children_;
    
    ///
    /// 親ノード
    ISceneNode* parent_;
    
    ///
    /// ノードID
    NodeID node_id_;
};


TRI_CORE_NS_END


#endif // TRI_TRANSFORM_NODE_HPP_INCLDED
