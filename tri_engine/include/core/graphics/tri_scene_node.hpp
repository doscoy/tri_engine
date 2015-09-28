////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_scene_node.hpp
    シーンノード.
*/

#ifndef dev_t3_tri_scene_node_h
#define dev_t3_tri_scene_node_h

//  include
#include "core/core_config.hpp"
#include "../math/tri_math.hpp"
#include "core/base/tri_std.hpp"


TRI_CORE_NS_BEGIN


//  前方宣言
class SceneGraph;
class ISceneNode;

///
/// ノード番号
using NodeID = uint32_t;

///
/// シーンノードポインタ
using SceneNodePtr = SharedPtr<ISceneNode>;



///
/// シーンノードインターフェース
class ISceneNode {

public:
    ///
    /// ノードIDを取得
    virtual NodeID getNodeID() const = 0;

    ///
    /// 更新
    virtual void onUpdate(
        SceneGraph* scene,  ///< シーングラフ
        tick_t delta_time   ///< デルタタイム
    ) = 0;

    ///
    /// 描画前処理
    virtual bool preRender(
        SceneGraph* scene   ///< シーングラフ
    ) = 0;

    ///
    /// 描画判定
    virtual bool isVisible(
        SceneGraph* scene_graph ///< シーングラフ
    ) const = 0;


    ///
    /// 描画
    virtual void render(
        SceneGraph* scene_graph ///< シーングラフ
    ) = 0;
    
    ///
    /// 子ノードを描画
    virtual void renderChildren(
        SceneGraph* scene_graph ///< シーングラフ
    ) = 0;
    
    ///
    /// 描画後処理
    virtual void postRender(
        SceneGraph* scene_graph ///< シーングラフ
    ) = 0;
    
    ///
    /// 子ノードを追加
    virtual bool addChild(
        SceneNodePtr kid    ///< 追加する子ノード
    ) = 0;
    
    ///
    /// 子ノードを削除
    virtual bool removeChild(
        NodeID id       ///< 削除するノードID
    ) = 0;
    
    ///
    /// 親ノード取得
    virtual ISceneNode* getParent() = 0;
    
    ///
    /// 親ノード取得
    virtual const ISceneNode* getParent() const = 0;
    
    ///
    /// 親ノード設定
    virtual void setParent(ISceneNode* p) = 0;
    
    ///
    /// デストラクタ
    virtual ~ISceneNode(){}
    
};


using SceneNodeList = Vector<SceneNodePtr>;

using RenderableSceneNodes = List<SceneNodePtr>;



TRI_CORE_NS_END

#endif
