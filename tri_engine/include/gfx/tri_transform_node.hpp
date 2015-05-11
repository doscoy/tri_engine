/**
    @file tri_transform_node.hpp
    トランスフォームノード.
*/

#ifndef TRI_TRANSFORM_NODE_HPP_INCLUDED
#define TRI_TRANSFORM_NODE_HPP_INCLUDED

//  include
#include "tri_scene_node.hpp"

namespace t3 {

//  前方宣言
class Entity;
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
    virtual NodeID getNodeID() const {
        return node_id_;
    }

    ///
    /// オブジェクトをアタッチ
    void attachEntity(
        Entity* entity
    ) {
        entity_ = entity;
    }
    
    ///
    /// オブジェクトをデタッチ
    void detachEntity() {
        entity_ = nullptr;
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
    virtual ISceneNode* getParent() {
        return parent_;
    }
    
    ///
    /// 親を取得
    virtual const ISceneNode* getParent() const {
        return parent_;
    }
    
    
    ///
    /// 親を設定
    virtual void setParent(
        ISceneNode* p
    ) {
        parent_ = p;
    }
    
    
    ///
    /// 更新
    void onUpdate(
        SceneGraph* scene_graph,
        tick_t delta_time
    ) override;
    
    
    ///
    /// 表示判定
    bool isVisible(
        SceneGraph* scene_graph ///< シーングラフ
    ) const override;
    
    
    ///
    /// 子ノードを描画
    virtual void renderChildren(
        SceneGraph* scene_graph
    );
    
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
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ = v;
    }
    
    ///
    /// 座標を取得
    const Vec3& position() const {
        return position_;
    }
    
    ///
    /// 座標を加算
    void addPosition(
        const Vec3& v
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
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        rotation_.x_ = x;
        rotation_.y_ = y;
        rotation_.z_ = z;
    }
    
    
    ///
    /// x軸回転を設定
    void setRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ = r;
    }
    
    ///
    /// y軸回転を設定
    void setRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ = r;
    }
    
    ///
    /// z軸回転を設定
    void setRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ = r;
    }
    
    ///
    /// 回転情報を設定
    void rotation(
        const Vec3& v
    ) {
        calc_request_ = true;
        rotation_ = v;
    }
    
    ///
    /// 回転情報を取得
    const Vec3& rotation() const {
        return rotation_;
    }
    
    ///
    /// x軸回転を加算
    void addRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ += r;
    }
    
    ///
    /// y軸回転を加算
    void addRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ += r;
    }
    
    ///
    /// ｚ軸回転を加算
    void addRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ += r;
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
        const Vec3& v
    ) {
        calc_request_ = true;
        scale_ = v;
    }
    
    ///
    /// スケール取得
    const Vec3& scale() const {
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
    Vec3 position_;
    
    ///
    /// 回転情報
    Vec3 rotation_;
    
    ///
    /// スケール
    Vec3 scale_;
    
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
    Entity* entity_;
    
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


}   // namespace t3


#endif // TRI_TRANSFORM_NODE_HPP_INCLDED
